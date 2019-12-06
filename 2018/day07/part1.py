#!/usr/bin/python3
# Example line: Step A must be finished before step L can begin.
edges = [(ord(x[1]) - ord('A'), ord(x[7]) - ord('A')) for x in map(lambda x: x.split(), open('input.in').readlines())]
workers = 5
for e in edges:
   print('{} → {}'.format(chr(ord('A') + e[0]),chr(ord('A') + e[1])))

class Node(object):
    def __init__(self, no):
        self.id = no
        self.inputs = {} 
        self.outputs = {}
    def insert_source(self, source_id, source):
        self.inputs[source_id] = source

    def insert_target(self, target_id, target):
        self.outputs[target_id] = target

    def __repr__(self):
        return str({ 'in': self.inputs.keys(), 'out': self.outputs.keys(), 'id': [self.id]})

graph = {}
for l in range(ord('Z') - ord('A') + 1):
    graph[l] = Node(l)

for source, target in edges:
    graph[source].insert_target(target, graph[target])
    graph[target].insert_source(source, graph[source])

output = []
nodes_to_insert = []
graph_len = len(graph)
while(len(output) < graph_len):
#    print(len(output))
#    print(len(graph))
    nodes_to_insert = []
    for node in graph:
#        print('{} : {} → {}'.format(node, len(graph[node].inputs), len(graph[node].outputs)))
#        print('{}: {}'.format(node, graph[node]))
        if len(graph[node].inputs) == 0:
            nodes_to_insert.append(node)
    print(nodes_to_insert)
    nodes_to_insert.sort()
    n = nodes_to_insert[0]
    if n in graph:
        output.append(n)
        for k in graph[n].outputs:
            out = graph[n].outputs[k]
            del out.inputs[n]
        print("Removing {}.".format(n))
        del graph[n]

result = [chr(ord('A') + x) for x in output]
print(result)
print(''.join(result))
