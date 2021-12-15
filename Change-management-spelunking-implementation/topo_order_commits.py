#!/usr/local/cs/bin/python3
#Jinbean Park
#805330751

import os, zlib, sys 

class CommitNode:
    def __init__(self, commit_hash):
        """
        :type commit_hash: str
        """
        self.commit_hash = commit_hash
        self.parents = set()
        self.children = set()

def search_git_direc(current_direc):
    try:
        list_files = os.listdir(current_direc)
    except:
        sys.stderr.write("The .git directory is not exist\n")
    
    if ".git" not in list_files and current_direc == "/":
        sys.stderr.write("The .git directory is not exist\n")
    
    if ".git" in list_files:
        return current_direc
    else:
        parent_direc = os.path.abspath(os.path.join(current_direc, os.pardir))
        return search_git_direc(parent_direc)

class commit_graph:
    def __init__(self):
        self.top_git_direc = search_git_direc(os.getcwd())
        self.root_commits = set()
        self.topo_order = []
        self.head_branches = {}
        self.commit_node_graph = {}
        commit_hash_list = self.get_list_local_branches()
        self.build_commit_graph(commit_hash_list)
        self.topological_sorting()

    def return_ref_dir(self):
        return self.top_git_direc + "/" + ".git/refs/heads/"
       
    def return_obj_dir(self):
        return self.top_git_direc + "/" + ".git/objects/"

    def get_list_local_branches(self):
        commit_hash_list = []
        list_branches = []

        for root, dir, files in os.walk(self.return_ref_dir()):
            for filename in files:
                list_branches.append(os.path.join(root, filename))
        for branch_file in list_branches:
            split_branch = branch_file.split('/')
            indx_head = split_branch.index('heads')
            branch_name = '/'.join(split_branch[indx_head + 1:])
            f = open(branch_file)
            hash_value = f.read()
            hash_value = hash_value.replace('\n', '')
            commit_hash_list.append(hash_value)
            if not hash_value in self.head_branches:
                self.head_branches[hash_value] = []
            self.head_branches[hash_value].append(branch_name)
            f.close()
        return commit_hash_list
        
    
    def build_commit_graph(self, commit_hash_list):
        while (len(commit_hash_list) > 0):
            commit_hash = commit_hash_list.pop(0)
            commit_node = CommitNode(commit_hash)
            self.commit_node_graph[commit_hash] = commit_node
            f = open (self.return_obj_dir() + commit_hash[0:2] + "/" + commit_hash[2:], 'rb')
            compress_hash = f.read()
            decompress_hash = zlib.decompress(compress_hash)
            commit_blob = str(decompress_hash).replace('\\n', ' ').split(' ')
            if 'parent' not in commit_blob:
                self.root_commits.add(commit_hash)
            while 'parent' in commit_blob:
                indx_parent = commit_blob.index('parent')
                parent_hash = commit_blob[indx_parent + 1]
                commit_blob.remove('parent')
                commit_node.parents.add(parent_hash)
                commit_hash_list.append(parent_hash)
            f.close()            
        for commit_hash in self.commit_node_graph:
            children = self.commit_node_graph[commit_hash]
            for parent in children.parents:
                self.commit_node_graph[parent].children.add(commit_hash)
    

    def topological_sorting(self):
        gray_stack = []
        sorted_root_commits = sorted(self.root_commits)
        stack = list(sorted_root_commits)
        visited = set()
        while (len(stack) > 0):
            top_element = stack.pop()
            if top_element in visited:
                continue
            visited.add(top_element)

            while len(gray_stack) > 0 and top_element not in self.commit_node_graph[gray_stack[-1]].children:
                g_top_element = gray_stack.pop()
                self.topo_order.append(g_top_element)
            gray_stack.append(top_element)

            sorted_commit_node_graph = sorted(self.commit_node_graph[top_element].children)
            for children in sorted_commit_node_graph:
                if children not in visited:
                    stack.append(children)
                else:
                    continue
        while gray_stack:
            self.topo_order.append(gray_stack.pop())


    def printing_commit_hashes(self):
        count_commit = 0
        string = ''
        for commit_hash in self.topo_order:
            if len(string) > 2 and '\n' == string[-2] == string[-1]:
                if self.commit_node_graph[commit_hash].children:
                    sorted_children = sorted(self.commit_node_graph[commit_hash].children)
                    children = ' '.join(sorted_children)
                else:
                    children = ''
                
                string += '=' + children + '\n'

            if commit_hash in self.head_branches.keys():
                string += commit_hash + ' ' + ' '.join(self.head_branches[commit_hash]) + '\n'
            else:
                string += commit_hash + '\n'

            if count_commit + 1 < len(self.topo_order):
                next_order = self.topo_order[count_commit + 1]
                if next_order not in self.commit_node_graph[commit_hash].parents:
                    sorted_parents = sorted(self.commit_node_graph[commit_hash].parents)
                    string += ' '.join(sorted_parents) + '=\n\n'
            count_commit += 1        
        return string


def topo_order_commits():
    Commit_Graph = commit_graph()
    print(Commit_Graph.printing_commit_hashes())
    
if __name__ == "__main__":
    topo_order_commits()