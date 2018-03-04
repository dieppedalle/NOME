/**
 * Copyright 2018 Toby Chen
 * All rights reserved
 */

#include "Octree.h"

BoundingBox FOctreeBase::getLooseExtent() const
{
    Vector3 halfSize = getExtent().HalfSize();
    return BoundingBox(getExtent().min_ - halfSize, getExtent().max_ + halfSize);
}

bool FOctreeBase::canFitInChild(const BoundingBox& box) const
{
    //We implement a loose octree with k=2
    //According to the original paper, box fits in a child iff. l <= L/4 = 1/2*W*(2^d)
    // W*(2^d) is the same thing as the width of current level
    auto halfActualL = getExtent().HalfSize();
    auto boxSize = box.Size();
    return boxSize.x_ <= halfActualL.x_ && boxSize.y_ <= halfActualL.y_ && boxSize.z_ <= halfActualL.z_;
}

bool FOctreeBase::isInside(const BoundingBox& box) const
{
    return getLooseExtent().IsInside(box) == INSIDE;
}
