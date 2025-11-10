#include <iostream>
#include <list>
#include <unordered_set>
using namespace std;

class FIFOPageReplacement {
private:
    list<int> pageQueue;          // to store pages in FIFO order
    unordered_set<int> pageSet;   // to check if a page is in memory
    int capacity;                 // maximum number of frames
    int pageHits;
    int pageMisses;

public:
    // Constructor
    FIFOPageReplacement(int capacity) {
        this->capacity = capacity;
        pageHits = 0;
        pageMisses = 0;
    }

    // Function to reference a page
    void referencePage(int page) {
        // If page is already present in memory (hit)
        if (pageSet.find(page) != pageSet.end()) {
            pageHits++;
            return;
        }

        // If frames are full, remove the oldest page (FIFO)
        if (pageQueue.size() == capacity) {
            int frontPage = pageQueue.front();
            pageQueue.pop_front();
            pageSet.erase(frontPage);
        }

        // Add new page
        pageQueue.push_back(page);
        pageSet.insert(page);
        pageMisses++;
    }

    // Getters
    int getPageHits() const {
        return pageHits;
    }

    int getPageMisses() const {
        return pageMisses;
    }

    float getHitRatio() const {
        return (float(pageHits) / float(pageHits + pageMisses)) * 100;
    }

    float getMissRatio() const {
        return (float(pageMisses) / float(pageHits + pageMisses)) * 100;
    }
};

// Main function
int main() {
    int capacity, n;
    cout << "Enter the number of frames: ";
    cin >> capacity;

    FIFOPageReplacement fifo(capacity);

    cout << "Enter the number of page references: ";
    cin >> n;

    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; i++) {
        int page;
        cin >> page;
        fifo.referencePage(page);
    }

    cout << "\nTotal Page Hits   : " << fifo.getPageHits();
    cout << "\nTotal Page Faults : " << fifo.getPageMisses();
    cout << "\nHit Ratio (%)     : " << fifo.getHitRatio();
    cout << "\nFault Ratio (%)   : " << fifo.getMissRatio() << endl;

    return 0;
}