# COMP4300 - Assignment2

## Program Specification

Implementing an Entity Manager utilizing a vector of entities for storage and an a map of entities to manage entities for quick retrieval.

## Entity Specifications
An Entity Class will support the following private fields:
- id
- tag
- alive bit
and the following public API using shared pointers:
- cTransform
- cName
- cShape
- cBBox
- Private friend Constructor(tag, id)
## Entity Manager Specifications
The Entity Manager supports Entity Additon (for docking), Updates (to render entities), 
