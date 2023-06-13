#include<bits/stdc++.h>
using namespace std;
struct TreeNode{
    char data;
    TreeNode* left;
    TreeNode* right;
};
unordered_map<string,char> fn(unordered_map<char,string>map){
    unordered_map<string,char>m;
    for(auto it:map){
        m[it.second]=it.first;
    }
    return m;
}
void addIntoPq(vector<int>v,priority_queue<pair<int,TreeNode*>,vector<pair<int,TreeNode*>>,greater<pair<int,TreeNode*>>>&pq){
     for(int i=0;i<v.size();i++){
        if(v[i]!=0){
            //cout<<char(i)<<" "<<v[i]<<endl;
            TreeNode* root=new TreeNode;
            root->data=char(i);
            root->left=NULL;
            root->right=NULL;
            pq.push({v[i],root});
        }
     }
     return;
}
TreeNode* create_Tree(priority_queue<pair<int,TreeNode*>,vector<pair<int,TreeNode*>>,greater<pair<int,TreeNode*>>>pq){
    pair<int,TreeNode*> min1;
    pair<int,TreeNode*> min2;
    while(pq.size()!=1){
     min1=pq.top();
     pq.pop();
     min2=pq.top();
     pq.pop();
     pair<int,TreeNode*>temp;
     temp.first=min1.first+min2.first;
     TreeNode* root=new TreeNode;
     root->data='\0';
     root->left=min1.second;
     root->right=min2.second;
     temp.second=root;
     pq.push(temp);
    }
    pair<int,TreeNode*>ans;
    ans=pq.top();
    return ans.second;
}
void saveCodes(TreeNode* root,unordered_map<char,string>&map,string s){
     if(!root) return;
     if(!root->right&&!root->left){
        //cout<<root->data<<" "<<s<<endl;
        map[root->data]=s;
        return;
     }
     else{
          //data;
          if(root->left)
          saveCodes(root->left,map,s+"0");
          if(root->right)
          saveCodes(root->right,map,s+"1");
     }
}
vector<int> readFile( ){
     vector<int>v(256,0);
     ifstream file("input.txt");
     if (!file) {
        cout << "Failed to open the file." <<endl;
        return v;
    }
    char c;
    while (file.get(c)) {
        v[int(c)]++;
    }
    file.close();
    return v;
}

void encodeFile(unordered_map<char,string>map){
    ifstream file("input.txt");
    ofstream file2("output.txt");
    char c;
    while(file.get(c)){
         string s=map[c];
         file2<<s;
         s="";
    }
    file.close();
    file2.close();
    return;
}
void decodeFile(unordered_map<string,char>m){
    ifstream file ("output.txt");
    ofstream file2("output2.txt");
    char c;
    string s="";
    while(file.get(c)){
        s+=c;
        if(m.count(s)){
            char ch=m[s];
            file2<<ch;
            s="";
        }
    }
    file.close();
    file2.close();
    return;
}
int main(){
    vector<int>v=readFile();
    priority_queue<pair<int,TreeNode*>,vector<pair<int,TreeNode*>>,greater<pair<int,TreeNode*>>>pq;
    addIntoPq(v,pq);
    TreeNode* root=create_Tree(pq);
    unordered_map<char,string>map;
    saveCodes(root,map,"");
    unordered_map<string,char>m;
    m=fn(map);
    encodeFile(map);
    decodeFile(m);
    return 0;
}