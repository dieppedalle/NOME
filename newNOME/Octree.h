/**
 * Copyright 2018 Toby Chen
 * All rights reserved
 */

#pragma once
#include <BoundingBox.h>
#include <Ray.h>
#include <set>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using std::set;
using std::vector;

class FOctreeBase
{
public:
    BoundingBox getLooseExtent() const;

    const BoundingBox& getExtent() const
    {
        return Extent;
    }

    void setExtent(const BoundingBox& value)
    {
        Extent = value;
    }

    //You should never use the base class directly
protected:
    FOctreeBase() = default;

    ~FOctreeBase() = default;

    bool canFitInChild(const BoundingBox& box) const;

    bool isInside(const BoundingBox& box) const;

private:
    BoundingBox Extent;
};

/**
 * FOctree is both the octree class and the octant class (recursive DS)
 * Member class must implement:
 *  setOctant
 *  getOctant
 *  getWorldAABB
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

    FOctree* getParent() const
    {
        return Parent;
    }

    void addHere(T* node)
    {
        Members.insert(node);
        node->setOctant(this);
    }

    void eraseHere(T* node)
    {
        if (node == nullptr)
            return;
        Members.erase(node);
        node->setOctant(nullptr);
    }

    void insert(T* member, int currDepth = 0)
    {
        if (currDepth < MaxDepth && canFitInChild(member->getWorldAABB()))
        {
            auto childOctant = determineAndCreateOctant(member->getWorldAABB());
            childOctant->insert(member, currDepth + 1);
        }
        else
        {
            addHere(member);
        }
    }

    void remove(T* member)
    {
        auto* octant = member->getOctant();
        if (octant)
            octant->eraseHere(member);

        member->setOctant(nullptr);
    }

    //Only call this at the root level
    void updateNode(T* member)
    {
        assert(Parent == nullptr);

        const BoundingBox& boundingBox = member->getWorldAABB();

        //Undefined boundingbox -> remove from octree
        if (!boundingBox.Defined())
        {
            remove(member);
        }
        else
        {
            //Not in tree -> insertion
            if (!member->getOctant())
            {
                if (getLooseExtent().IsInside(boundingBox) != INSIDE)
                    addHere(member);
                else
                    insert(member);
            }
            else
            {
                FOctree* currOctant = member->getOctant();
                if (!currOctant->isInside(boundingBox))
                {
                    remove(member);
                    if (getLooseExtent().IsInside(boundingBox) != INSIDE)
                        addHere(member);
                    else
                        insert(member);
                }
            }
        }
    }

    const set<T*>& getMembers() const
    {
        return Members;
    }

    void printTree(int level = 0) const
    {
        printf("Level: %d\n", level);
        for (T* member : Members)
        {
            std::cout << member->toString() << std::endl;
        }
        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
                for (int z = 0; z < 2; z++)
                    if (Children[x][y][z])
                    {
                        printf("Child: %d %d %d\n", x, y, z);
                        Children[x][y][z]->printTree(level + 1);
                    }
    }

    void findNodes(const Ray& ray, vector<T*>& result, bool individualTesting = true)
    {
        BoundingBox extent = getLooseExtent();
        if (ray.HitDistance(extent) == M_INFINITY)
            return;
        if (individualTesting)
        {
            for (T* m : Members)
            {
                const BoundingBox& memberBox = m->getWorldAABB();
                if (ray.HitDistance(memberBox) != M_INFINITY)
                    result.push_back(m);
            }
        }
        else
        {
            for (T* m : Members)
                result.push_back(m);
        }

        for (int x = 0; x < 2; x++)
            for (int y = 0; y < 2; y++)
                for (int z = 0; z < 2; z++)
                    if (Children[x][y][z])
                    {
                        Children[x][y][z]->findNodes(ray, result, individualTesting);
                    }
    }

private:
    FOctree* Parent;
    FOctree* Children[2][2][2];

    set<T*> Members;

    FOctree* determineAndCreateOctant(const BoundingBox& box)
    {
        auto center = getExtent().Center();
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
            auto& extent = getExtent();
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
            Children[x][y][z]->setExtent({min, max});
        }

        return Children[x][y][z];
    }
};

//Convenient definition here
class OctreeProxy;
typedef FOctree<OctreeProxy, 8> OctantNew;
