1. Cluster centroid calculation can be optimized by checking if the cluster has been updated.
2. Parent population shouldn't be reused until it's the population is updated since
descendants don't relate in any way to the parent population. Thus a descendants new vector
should be created.
3. populationReplacement() should be renamed to populationUpdate() since some members may be kept
4. Cromosome shall be model as a class called shaped that must be responsable of calculating the
a configuration fitness by means of clusters.
5. The only inheritance relation to keep is the GeneticAlgorithm branch. GeneticAlgorithm must be an
abstract class. Regarding ES and BL: the only functions that ES legitimatly uses from BL are
initializeIfs, updateIfs. Although exploreNeighbourhud is defined in BL, it is actually never used
in BL, it's only used in ES. The rest are functions related to shaping and clusters. Thus, they are
not of the same type. On the other hand, ILS and ILSES are the same thing although their
optimumSearcher is different. ILS uses BL, while ILSES uses ES. They should be model as the same class,
using dependencyInyection better than inheritance since no state is used in the optimumSearcher.
6. There should only be one way of representing state, namely shaping. This object shall be responsable
for implementing every single functionality needed to operate with shaping and clusters. It can use
clusters internally as well as vector of points.
7. The execution parameters class shall be broken in order to implement concurrency, since global state
is not possible.
8. Usar archivos de configuracion

