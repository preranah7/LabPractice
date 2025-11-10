#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>
using namespace std;

class OptimalPageReplacement {
private:
    int capacity;                  // Number of frames
    vector<int> pages;             // Reference string
    int n;                         // Number of page references
    int pageHits;
    int pageFaults;

public:
    // Constructor
    OptimalPageReplacement(int capacity, const vector<int>& pages) {
        this->capacity = capacity;
        this->pages = pages;
        this->n = pages.size();
        pageHits = 0;
        pageFaults = 0;
    }

    // Function to find the page to replace
    int predictPageToReplace(const vector<int>& frames, int index) {
        int farthest = index;
        int pageToReplace = -1;

        for (int i = 0; i < frames.size(); i++) {
            int j;
            for (j = index; j < n; j++) {
                if (frames[i] == pages[j]) {
                    if (j > farthest) {
                        farthest = j;
                        pageToReplace = i;
                    }
                    break;
                }
            }
            // If a page is never referenced again, replace it
            if (j == n)
                return i;
        }

        // If all pages are referenced in future, replace the farthest one
        return (pageToReplace == -1) ? 0 : pageToReplace;
    }

    // Run Optimal Page Replacement algorithm
    void run() {
        vector<int> frames;
        for (int i = 0; i < n; i++) {
            int currentPage = pages[i];

            // If page already exists (hit)
            bool found = false;
            for (int p : frames) {
                if (p == currentPage) {
                    found = true;
                    pageHits++;
                    break;
                }
            }

            // If not found â page fault
            if (!found) {
                pageFaults++;
                // If space available, insert directly
                if (frames.size() < capacity)
                    frames.push_back(currentPage);
                else {
                    // Replace using Optimal prediction
                    int idx = predictPageToReplace(frames, i + 1);
                    frames[idx] = currentPage;
                }
            }
        }
    }

    // Display results
    void displayResults() {
        cout << "\nTotal Page Hits   : " << pageHits;
        cout << "\nTotal Page Faults : " << pageFaults;
        float hitRatio = (float(pageHits) / float(n)) * 100;
        float faultRatio = (float(pageFaults) / float(n)) * 100;
        cout << "\nHit Ratio (%)     : " << hitRatio;
        cout << "\nFault Ratio (%)   : " << faultRatio << endl;
    }
};

// Main function
int main() {
    int capacity, n;
    cout << "Enter number of frames: ";
    cin >> capacity;

    cout << "Enter number of page references: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the page reference string:\n";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    OptimalPageReplacement opr(capacity, pages);
    opr.run();
    opr.displayResults();

    return 0;
}