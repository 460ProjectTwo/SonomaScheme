#ifndef _astnode_h_
#define _astnode_h_

#include <memory>
#include <vector>

#include "CodeGenerator.h"

class ASTNode
{
 public:
    using Ref = std::unique_ptr<ASTNode const>;
    virtual ~ASTNode() = default;
    std::vector<Ref> const & Children() const;
    virtual void GenerateCode(CodeGen *) const = 0;

 protected:
    std::vector<Ref> _children;
};

#endif // _astnode_h_
