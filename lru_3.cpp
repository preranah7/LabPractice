#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class LRUPageReplacement {
private:
    int capacity;                              // Number of frames
    list<int> pageList;                        // Stores pages, most recent at front
    unordered_map<int, list<int>::iterator> pageMap; // Maps page number to its position
    int pageHits;
    int pageFaults;

public:
    // Constructor
    LRUPageReplacement(int capacity) {
        this->capacity = capacity;
        pageHits = 0;
        pageFaults = 0;
    }

    // Reference a page
    void referencePage(int page) {
        // If page is already in cache (HIT)
        if (pageMap.find(page) != pageMap.end()) {
            pageHits++;
            // Move page to the front (most recently used)
            pageList.erase(pageMap[page]);
            pageList.push_front(page);
            pageMap[page] = pageList.begin();
        } else {
            // Page fault
            pageFaults++;

            // If cache is full, remove least recently used (back)
            if (pageList.size() == capacity) {
                int last = pageList.back();
                pageList.pop_back();
                pageMap.erase(last);
            }

            // Insert new page at front
            pageList.push_front(page);
            pageMap[page] = pageList.begin();
        }
    }

    // Getters
    int getPageHits() const {
        return pageHits;
    }

    int getPageFaults() const {
        return pageFaults;
    }

    float getHitRatio() const {
        return (float(pageHits) / float(pageHits + pageFaults)) * 100;
    }

    float getFaultRatio() const {
        return (float(pageFaults) / float(pageHits + pageFaults)) * 100;
    }
};

// Main function
int main() {
    int capacity, n;
    cout << "Enter number of frames: ";
    cin >> capacity;

    LRUPageReplacement lru(capacity);

    cout << "Enter number of page references: ";
    cin >> n;

    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; i++) {
        int page;
        cin >> page;
        lru.referencePage(page);
    }

    cout << "\nTotal Page Hits   : " << lru.getPageHits();
    cout << "\nTotal Page Faults : " << lru.getPageFaults();
    cout << "\nHit Ratio (%)     : " << lru.getHitRatio();
    cout << "\nFault Ratio (%)   : " << lru.getFaultRatio() << endl;

    return 0;

}

Enter number of frames: 3
Enter number of page references: 12
Enter the page reference string:
1 2 3 2 4 1 5 2 1 2 3 4
