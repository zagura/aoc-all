#!/usr/bin/python3
# Example line: Step A must be finished before step L can begin.
edges = [(ord(x[1]) - ord('A'), ord(x[7]) - ord('A')) for x in 
map(lambda x: x.split(), open('input.in').readlines())]
workers = 5
for e in edges:
   print('{} → {}'.format(chr(ord('A') + e[0]),chr(ord('A') + e[1])))

class Node(object):
    def __init__(self, no):
        self.id = no
        self.inputs = {} 
        self.outputs = {}
        self.begin_time = 0
        self.end_time = -1
        self.busy = -1
    def insert_source(self, source_id, source):
        self.inputs[source_id] = source

    def insert_target(self, target_id, target):
        self.outputs[target_id] = target

    def __repr__(self):
        return str({ 'in': self.inputs.keys(), 'out': self.outputs.keys(), 'id': [self.id]})

graph = {}
# for l in range(ord('Z') - ord('A') + 1):
#     graph[l] = Node(l)

for source, target in edges:
    if source not in graph:
        graph[source] = Node(source)
    if target not in graph:
        graph[target] = Node(target)
    graph[source].insert_target(target, graph[target])
    graph[target].insert_source(source, graph[source])

output = []
nodes_to_insert = []
graph_len = len(graph)
time_point = 0
workers = [ -1 for i in range(6)]
while(len(output) < graph_len):
#    print(len(output))
#    print(len(graph))
    for w in range(len(workers)):
        nodes_to_insert = []
        for node in graph:
    #        print('{} : {} → {}'.format(node, len(graph[node].inputs), len(graph[node].outputs)))
    #        print('{}: {}'.format(node, graph[node]))
            if len(graph[node].inputs) == 0:
                nodes_to_insert.append(node)
        #print(nodes_to_insert)
        if len(nodes_to_insert) == 0:
            print('Total time: {} .'.format(time_point))
            break
        nodes_to_insert.sort()
        limit = min(len(workers), len(nodes_to_insert))
        processed_nodes = nodes_to_insert[:limit]
        for n in processed_nodes:
            if n in graph:
                if w != 0 and workers[w] == -1 and graph[n].busy == -1:
                    print('Assigning {} to worker {} at time point: {}'.format(chr(n+ord('A')), w, time_point))
                    graph[n].begin_time = time_point
                    graph[n].end_time = time_point  + n + 1 + 60
                    workers[w] = n
                    graph[n].busy = w
                if time_point == graph[n].end_time and graph[n].busy >= 0 and w == 0:
                    for k in graph[n].outputs:
                        out = graph[n].outputs[k]
                        del out.inputs[n]
                    print("Removing {} TP {}.".format(n, time_point))
                    output.append(n)
                    workers[graph[n].busy] = -1
                    graph[n].busy = -1
                    del graph[n]

    time_point += 1


print('Total time: {} .'.format(time_point))
