#include "OctreeProxy.h"
#include "Data.h"

const BoundingBox& VertOctreeProxy::getWorldAABB() const {
    return worldAABB;
}

VertOctreeProxy::VertOctreeProxy(OctantNew* root, Vert* owner, int x, int y, int z) : OctreeProxy(root), Owner(owner) {
    updateWorldPosition(x, y, z);
}

void VertOctreeProxy::updateWorldPosition(float x, float y, float z) {
    Vector3 halfRadius = Vector3(HALF_RADIUS, HALF_RADIUS, HALF_RADIUS);
    Vector3 center = Vector3(x, y, z);
    worldAABB = BoundingBox(center - halfRadius, center + halfRadius);

    octreeRoot->updateNode(this);
}

std::string VertOctreeProxy::toString() const
{
    return "Name:" + Owner->getFullName() + " BB(" + worldAABB.ToString() + ") index:" + std::to_string(Owner->index);
}

int VertOctreeProxy::getIndex(EProxyType type) const
{
    if (type == EProxyType::Vert)
        return Owner->index;
    return -1;
}
