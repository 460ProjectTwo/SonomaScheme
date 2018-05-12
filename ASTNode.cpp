#include "ASTNode.h"

using namespace std;

vector<ASTNode::Ref> const& ASTNode::Children() const
{
    return _children;
}
