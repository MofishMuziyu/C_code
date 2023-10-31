ADT Half_edge{
    Data:
        所有的半边  
        所有的点
        所有的面
    Operations：
        Init: 
            Input:                  一条半边以及半边对应的指针的名称
            Preconditions:          无
            Process:                将该半边的各值分别赋予初值
            Output:                 无
            Postcondition:          无

        Traverse_edge_surface:      //遍历边周围的所有面
            Input:                  //一条半边
            Preconditions:          //无
            Process:                //不断遍历某条半边对应的面，再取该半边对应的相反半边的对应的面，直到等于原来半边
            Output:                 //在遍历过程中读取面的信息，或最后输出面的集合
            Postcondition:          //无


        Traverse_vertex_surface:    //遍历某个点的相邻的面
            Input:                  //一个点  
            Preconditions:          //无
            Process:                //先取该点对应的半边，取半边对应的面，再对半边不断取相反半边再取下一个半边，直到与原来半边重复
            Output:                 //在遍历过程中读取面的信息，或者记录后输出面的集合
            Postcondition:          //无

        Traverse_vertex_edge:       // 遍历一个点周围的所有边
            Input:                  //一个点
            Preconditions:          //无
            Process:                //取该点对应的半边，一直取相反的半边的下一个半边，直到与初始半边重复，遍历完成
            Output:                 //在遍历过程中读取边的信息或者记录，在最后输出边的组合
            Postcondition:          //无
        
        Face_edge:                  //遍历一个面的所有边
            Input:                  //一个面
            Preconditions:          //无
            Process:                //取出一个面对应的半边，然后，不断取下一个半边，直到与最初的半边重复
            Output:                 //在遍历过程中读取边的信息，记录，可以在最后输出边的组合    
            Postcondition:          //无


        Face_face:                  //遍历一个面周围的所有的面
            Input:                  //一个面
            Preconditions:          //无
            Process:                //取出一个面对应的半边，该半边的相反半边对应的面即为相邻的面，继续取原来半边的下一个半边，取相反的半边对应的面，
                                    //直到与初始的半边重合
            Output:                 //在遍历过程中读取面的信息，记录，可以在最后输出边的组合    
            Postcondition:          //无
}