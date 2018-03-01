#pragma once
#include <BoundingBox.h>
#include <set>

using std::set;

class FOctreeBase
{
public:
    const BoundingBox& GetExtent() const
    {
        return Extent;
    }

    void SetExtent(const BoundingBox& value)
    {
        Extent = value;
    }

    //You should never use the base class directly
protected:
    FOctreeBase() = default;

    ~FOctreeBase() = default;

    bool CanFitInChild(const BoundingBox& box) const;

private:
    BoundingBox Extent;
};

/**
 * FOctree is both the octree class and the octant class (recursive DS)
 * Member class must implement:
 *  SetOctant
 *  GetOctant
 *  GetWorldAABB
 */
template <typename T, unsigned int MaxDepth = 8>
class FOctree : public FOctreeBase
{
public:
    explicit FOctree(FOctree* parent = nullptr) : Parent(parent), Children{0}
    {
    }

    ~FOctree()
    {
        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
                for (int z = 0; z < 2; z++)
                    delete Children[x][y][z];
    }

    FOctree* GetParent() const
    {
        return Parent;
    }

    void AddHere(T* node)
    {
        Members.insert(node);
        node->SetOctant(this);
    }

    void EraseHere(T* node)
    {
        if (node == nullptr)
            return;
        Members.erase(node);
        node->SetOctant(nullptr);
    }

    void Insert(T* member, int currDepth = 0)
    {
        if (currDepth < MaxDepth && CanFitInChild(member->GetWorldAABB()))
        {
            auto childOctant = DetermineAndCreateOctant(member->GetWorldAABB());
            childOctant->Insert(member, currDepth + 1);
        }
        else
        {
            AddHere(member);
        }
    }

    void Remove(T* member)
    {
        auto* octant = member->GetOctant();
        if (octant)
            octant->EraseHere(member);

        member->SetOctant(nullptr);
    }

private:
    FOctree* Parent;
    FOctree* Children[2][2][2];

    set<T*> Members;

    FOctree* DetermineAndCreateOctant(const BoundingBox& box)
    {
        auto center = GetExtent().Center();
        auto boxCenter = box.Center();
        int x = 0, y = 0, z = 0;
        if (boxCenter.x_ > center.x_)
            x = 1;
        if (boxCenter.y_ > center.y_)
            y = 1;
        if (boxCenter.z_ > center.z_)
            z = 1;

        if (Children[x][y][z] == nullptr)
        {
            //Create child Octree and calculate its extent
            auto& extent = GetExtent();
            auto extentMiddle = extent.Center();
            Vector3 min, max;
            if (x == 0)
            {
                min.x_ = extent.min_.x_;
                max.x_ = extentMiddle.x_;
            }
            else
            {
                min.x_ = extentMiddle.x_;
                max.x_ = extent.max_.x_;
            }

            if (y == 0)
            {
                min.y_ = extent.min_.y_;
                max.y_ = extentMiddle.y_;
            }
            else
            {
                min.y_ = extentMiddle.y_;
                max.y_ = extent.max_.y_;
            }

            if (z == 0)
            {
                min.z_ = extent.min_.z_;
                max.z_ = extentMiddle.z_;
            }
            else
            {
                min.z_ = extentMiddle.z_;
                max.z_ = extent.max_.z_;
            }
            Children[x][y][z] = new FOctree(this);
            Children[x][y][z]->SetExtent({min, max});
        }

        return Children[x][y][z];
    }
};
