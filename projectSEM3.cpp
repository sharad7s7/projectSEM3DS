#include <iostream>
#include <string>
using namespace std;

class sVoter {
public:
    int id;
    string name;
    int votes;
    sVoter* left;
    sVoter* right;

    sVoter(int id, string name) : id(id), name(name), votes(0), left(nullptr), right(nullptr) {}
};

class sBST {
private:
    sVoter* root;

    sVoter* sinsert(sVoter* node, int id, string name) {
        if (node == nullptr)
            return new sVoter(id, name);

        if (id < node->id)
            node->left = sinsert(node->left, id, name);
        else if (id > node->id)
            node->right = sinsert(node->right, id, name);

        return node;
    }

    sVoter* ssearch(sVoter* node, int id) {
        if (node == nullptr || node->id == id)
            return node;

        if (id < node->id)
            return ssearch(node->left, id);

        return ssearch(node->right, id);
    }

    void sdisplayVotes(sVoter* node) {
        if (node == nullptr)
            return;

        sdisplayVotes(node->left);
        cout << "Candidate ID: " << node->id << ", Name: " << node->name << ", Votes: " << node->votes << endl;
        sdisplayVotes(node->right);
    }

public:
    sBST() : root(nullptr) {}

    void saddVoter(int id, string name) {
        root = sinsert(root, id, name);
    }

    sVoter* sfindVoter(int id) {
        return ssearch(root, id);
    }

    void svoteForCandidate(int id) {
        sVoter* candidate = sfindVoter(id);
        if (candidate) {
            candidate->votes++;
            cout << "Voted successfully for " << candidate->name << ". Total votes: " << candidate->votes << endl;
        } else {
            cout << "Candidate not found." << endl;
        }
    }

    void sshowAllVotes() {
        sdisplayVotes(root);
    }
};

void svoteForElection(sBST& bst) {
    int candidateID;
    cout << "Enter candidate ID to vote: ";
    cin >> candidateID;
    bst.svoteForCandidate(candidateID);
}

int main() {
    sBST bst;
    int numCandidates;

    cout << "Enter the number of candidates to register: ";
    cin >> numCandidates;

    for (int i = 0; i < numCandidates; ++i) {
        int id;
        string name;
        cout << "Enter ID for candidate " << (i + 1) << ": ";
        cin >> id;
        cout << "Enter name for candidate " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, name);
        bst.saddVoter(id, name);
    }

    int choice;
    do {
        cout << "\n-----------------------------\n";
        cout << "Voting Options:\n";
        cout << "1. Vote for an election\n";
        cout << "2. Show all votes\n";
        cout << "0. Exit\n";
        cout << "-----------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                svoteForElection(bst);
                break;
            case 2:
                bst.sshowAllVotes();
                break;
            case 0:
                cout << "Exiting.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
