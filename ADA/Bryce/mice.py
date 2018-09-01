def minimo(distancias,Q):
    mini=list(Q)[0]
    for i in Q:
        if distancias[mini]>distancias[i]:
            mini=i
    return mini




def dijkstra(G,s):
    distancia={}
    visto={}
    Q=set()
    prev={}

    for vertice in G:
        distancia[vertice]=float('inf')
        prev[vertice]=None
        Q.add(vertice)

    distancia[s]=0
    print(Q)
    while len(Q)!=0:
        u=minimo(distancia,Q)
        #print(u)
        Q.remove(u)
        #print(G[u])
        for vecino,peso in G[u].items():
            alt=distancia[u]+ peso
            #print "\t",distancia[u]
            if alt<distancia[vecino]:
                #print("entra")
                distancia[vecino]=alt
                prev[vecino]=u

    return distancia,prev


G={
    1:{2:7,3:9,6:14},
    2:{1:7,3:10,4:15},
    3:{1:9,2:10,4:11,6:2},
    4:{2:15,3:11,5:6},
    5:{4:6,6:9},
    6:{5:9,3:2,1:14}
}

print(dijkstra(G,1))
