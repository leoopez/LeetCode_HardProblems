class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        //nodes in DFS
        stack<TreeNode*> nodes;

        //value of new_node
        int number = 0;
        auto c = S.begin();

        //val of get root
        while(c != S.end() && *c != '-'){
            number = number*10 + (int)*c - 48;
            ++c;
        }
        //create root and start DFS
        TreeNode* root = new TreeNode(number);
        nodes.push(root);

        //Start counts
        //temp is the previous node depth
        int depth = 0, prev = 0;
        number = 0;

        //Algorithm
        for(auto i = c; i != S.end() ; ++i){
            //counter depth
            while(i != S.end() && *i == '-'){
                ++depth;
                ++i;
            }
            //get number
            while(i != S.end() && *i != '-'){
                number = number*10 + (int)*i - 48;
                ++i;
            }
            //new node with value of number
            TreeNode* new_node = new TreeNode(number);
            //if prev depth is minor than depth, new node on left
            if(prev < depth){
                nodes.top()->left = new_node;
                nodes.push(new_node);
                prev = depth;
            }
                //if prev depth is mayor than depth, new node on right
            else if(prev > depth){
                for(int k = 0 ; k<prev-depth+1; k++){
                    nodes.pop();
                }
                nodes.top()->right = new_node;
                nodes.push(new_node);
                prev = depth;
            }
                //prev depth is equal than depth, new node on rigth and complete two childs and pop of nodes
            else{
                nodes.pop();
                nodes.top()->right = new_node;
                nodes.push(new_node);
                prev = depth;
            }

            //the las while end with '-', so starts with count at 1
            number = 0;
            depth = 1;
            // skip runtime error for pass it == S.end() in the last while loop
            if(i == S.end()) break;
        }
        return root;
    }
};