#!/usr/bin/python3
# Example line: Step A must be finished before step L can begin.
edges = [(ord(x[1]) - ord('A'), ord(x[7]) - ord('A')) for x in map(lambda x: x.split(), open('input.in').readlines())]

for e in edges:
    print('{} → {}'.format(chr(ord('A') + e[0]),chr(ord('A') + e[1])))
class Node(object):
    def __init__(self, no, ins=[], outs=[]):
        self.id = no
        self.inputs = ins
        self.outputs = outs
        self.base_prio = 0
        self.no_prio = no

    def get_priority(self):
        return self.base_prio * 100 + self.no_prio
    def count_priorities(self, graph):
        if self.base_prio == 0:
            total_prio = 0 
            for c in self.inputs:
                total_prio = max(total_prio, graph[c].count_priorities(graph))
            self.base_prio = total_prio + 1
        return self.base_prio
    def __repr__(self):
        return str(self.__dict__)

def get_prio(node):
    return node.base_prio * 100 + node.no_prio
graph = {}
for e in edges:
    i_node = e[1]
    o_node = e[0]
    if i_node not in graph:
        graph[i_node] = Node(i_node, [])
    if o_node not in graph:
        graph[o_node] = Node(o_node, [])
    l = graph[o_node].inputs
    l.append(i_node)
    graph[o_node].inputs = l
#    print(graph[o_node])

#print(graph)


for node in graph.values():
    node.count_priorities(graph)


output = graph.values()

sorted_out = sorted(output,key=lambda x:get_prio(x))

result = [ chr(ord('A') + x.id) for x in sorted_out ]
result2 = [(chr(ord('A') + x.id), x.base_prio ) for x in sorted_out]
print(result2)
print(''.join(result[::-1]))
