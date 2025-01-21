//// 概念：
//
// 二分图
// 平面图
//
// 匹配（独立边集）
//
// 点双连通：
// 在一张连通的无向图中，对于两个点 u 和 v，删去任何一个点（只能删去一个，
// 且不能删 u 和 v 自己）它们依旧连通，则称 u 和 v 边双连通。
// 如果一个图不存在割点，那么它是一个点双连通图。
//
// 边双连通
//
// 无向正权图上某一点的偏心距： ecc(u) = max(dist[u][v])
// 即以该点为源点，到其他点所有最短路的最大值。
//
// 图的直径：最大的偏心距
//
// 图的中心：偏心距最小的点
//
// 图的绝对中心（可以定义在边上的中心）
//
// 图的半径：中心的偏心距


//// 结论：
//
// 1. 有向图判是否存在环直接用 topsort；无向图判是否存在环直接用 dsu，也可以使用 topsort，条
//    件变为 deg[i] <= 1 时入队
