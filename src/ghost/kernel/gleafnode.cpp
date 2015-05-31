#include "gleafnode_p_p.h"
#include "gleafnode_p_p.h"

// class GLeafNode

GLeafNode::GLeafNode(GLeafNodePrivate &dd, QObject *parent)
    : GGhostNode(dd, parent)
{
}

// class GLeafNodePrivate

GLeafNodePrivate::GLeafNodePrivate(Ghost::NodeType nodeType)
    : GGhostNodePrivate(Ghost::LeafNode, nodeType)
{
}

GLeafNodePrivate::~GLeafNodePrivate()
{
}
