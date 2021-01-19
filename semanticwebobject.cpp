#include "semanticwebobject.h"
SemanticWebObject::SemanticWebObject(){}
QString SemanticWebObject::GetName(){
    return Name;
}
void SemanticWebObject::SetName(QString Name){
    this->Name=Name;
}
