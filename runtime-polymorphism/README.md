# Runtime Polymorphism

## Goals
Write all code as library code
- better reuse
- easy testable

## Basic interface
Directly depending on the type

## Basic polymorphism
Use virtual base class, but changed the semantics of the document type.
Now it can only be a class or struct which inherits from the base class, but not an int

Disadvantage of the API:
- Client has to take care of memory management and inheritance
- Implementation class is always heap allocated
- Access to implementation class must be synchronized

## Advanced polymorphism

### 1. Step
Encapsulate int in an own class