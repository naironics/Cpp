#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    Node() { mContent = ' '; mMarker = false; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    bool wordMarker() { return mMarker; }
    void setWordMarker() { mMarker = true; }
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    bool mMarker;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setWordMarker();
    }
}


bool Trie::searchWord(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( current->wordMarker() )
            return true;
        else
            return false;
    }

    return false;
}


// Test program
int main()
{
    Trie* trie = new Trie();
    trie->addWord("Audi");
    trie->addWord("Audible");
    trie->addWord("Audacious");
    trie->addWord("Brave");
    trie->addWord("Bravo");
    trie->addWord("Bold");
    trie->addWord("Bill");
    trie->addWord("Courage");
    trie->addWord("Coldplay");
    trie->addWord("Eager");
    trie->addWord("Enigma");
    trie->addWord("Statutory");
    trie->addWord("Trailblazer");
    trie->addWord("Torrential");
    trie->addWord("Voluptous");
    trie->addWord("Zeal");
    trie->addWord("Zenith");



    if ( trie->searchWord("Audacious") )
        cout << "Found Audacious" << endl;

    if ( trie->searchWord("Moon") )
        cout << "Found Moon" << endl;

    if ( trie->searchWord("Enigma") )
        cout << "Found Enigma" << endl;

    if ( trie->searchWord("Rome") )
        cout << "Found Rome" << endl;

    if ( trie->searchWord("Zenith") )
        cout << "Found Zenith" << endl;

    delete trie;
}
