#pragma once
#include "Octree.h"
#include <BoundingBox.h>

class Vert;

enum class EProxyType
{
    Vert
};

class OctreeProxy
{
public:
    explicit OctreeProxy(OctantNew* root) : octreeRoot(root), octant(nullptr) {}

    ~OctreeProxy()
    {
        if (octreeRoot)
            octreeRoot->remove(this);
    }

    OctantNew* getOctant() const {
        return octant;
    }

    void setOctant(OctantNew* value) {
        octant = value;
    }

    virtual const BoundingBox& getWorldAABB() const = 0;

    virtual std::string toString() const = 0;

    virtual int getIndex(EProxyType type) const
    {
        return -1;
    }

protected:
    OctantNew* octreeRoot;

private:
    OctantNew* octant;
};

class VertOctreeProxy : public OctreeProxy
{
public:
    VertOctreeProxy(OctantNew* root, Vert* owner, int x, int y, int z);

    const BoundingBox& getWorldAABB() const override;

    void updateWorldPosition(float x, float y, float z);

    std::string toString() const override;

    int getIndex(EProxyType type) const override;

    Vert* getOwner() { return Owner; }

private:
    static constexpr float HALF_RADIUS = 0.05f;

    BoundingBox worldAABB;

    Vert* Owner;
};
