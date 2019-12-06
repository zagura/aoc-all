#!/usr/bin/python3

input_file = 'input.in'
data_file = list(map(lambda x: int(x), 
            open(input_file).read().split()))


class TNode(object):
    def __init__(self, no, children_count=0, metadata_count=0):
        self.no = no
        self.children_count = children_count
        self.metadata_count = metadata_count
        self.children = []
        self.metadata = []
    
    def put_data(self, data):
        self.children_count = data[0]
        self.metadata_count = data[1]
        child_data = data[2:]
        for i in range(self.children_count):
            child = TNode(self.no + 1)
            child_data = child.put_data(child_data)
            self.children.append(child)
        self.metadata = child_data[:self.metadata_count]
        if len(child_data) > self.metadata_count:
            return child_data[self.metadata_count:] 
        return []
    
    def sum_metadata(self):
        total = 0
        for c in self.children:
            total += c.sum_metadata()
        total += sum(self.metadata)
        return total
    
    def __repr__(self):
        return str(self.__dict__)

root = TNode(0)
root.put_data(data_file)
total_metadata = root.sum_metadata()
print(total_metadata)



