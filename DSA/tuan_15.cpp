#include <iostream>
#include <string>

using namespace std;

typedef struct Subsubsection {
    string name;
    int page_L;                                 // con trái
    int page_R;                                 // con phải
    Subsubsection* next;

    Subsubsection(string n, int l, int r) : name(n), page_L(l), page_R(r), next(nullptr) {}
} *subsubsection;

typedef struct Subsection {
    string name;
    int totalPages;
    Subsection* next;
    subsubsection head;

    Subsection(string n) : name(n), totalPages(0), next(nullptr), head(nullptr) {}
} *subsection;

typedef struct Section {
    string name;
    int totalPages;
    Section* next;
    subsection head;

    Section(string n) : name(n), totalPages(0), next(nullptr), head(nullptr) {}
} *section;

typedef struct Chapter {
    string name;
    int totalPages;
    Chapter* next;
    section head;

    Chapter(string n) : name(n), totalPages(0), next(nullptr), head(nullptr) {}
} *chapter;

typedef struct Book {
    string name;
    int totalPages;
    Book* next;
    chapter head;

    Book(string n) : name(n), totalPages(0), next(nullptr), head(nullptr) {}
} *book;

// Hàm cập nhật số trang của Subsubsection
void updatePageCountSubsubsection(subsubsection my_subsubsection) {
    // Subsubsection đã có số trang cố định (page_R - page_L + 1)
}

// Hàm cập nhật số trang của Subsection
void updatePageCountSubsection(subsection my_subsection) {
    int totalPages = 0;
    subsubsection current = my_subsection->head;
    while (current != nullptr) {
        totalPages += (current->page_R - current->page_L + 1);
        current = current->next;
    }
    my_subsection->totalPages = totalPages;
}

// Hàm cập nhật số trang của Section
void updatePageCountSection(section my_section) {
    int totalPages = 0;
    subsection current = my_section->head;
    while (current != nullptr) {
        updatePageCountSubsection(current);
        totalPages += current->totalPages;
        current = current->next;
    }
    my_section->totalPages = totalPages;
}

// Hàm cập nhật số trang của Chapter
void updatePageCountChapter(chapter my_chapter) {
    int totalPages = 0;
    section current = my_chapter->head;
    while (current != nullptr) {
        updatePageCountSection(current);
        totalPages += current->totalPages;
        current = current->next;
    }
    my_chapter->totalPages = totalPages;
}

// Hàm cập nhật tổng số trang của Book
void updatePageCountBook(book my_book) {
    int totalPages = 0;
    chapter currentChapter = my_book->head;

    while (currentChapter != nullptr) {
        int chapterPages = 0;
        section currentSection = currentChapter->head;

        while (currentSection != nullptr) {
            int sectionPages = 0;
            subsection currentSubsection = currentSection->head;

            while (currentSubsection != nullptr) {
                int subsectionPages = 0;
                subsubsection currentSubsubsection = currentSubsection->head;

                // Cập nhật số trang cho từng Subsubsection
                while (currentSubsubsection != nullptr) {
                    int subsubsectionPages = currentSubsubsection->page_R - currentSubsubsection->page_L + 1;
                    subsectionPages += subsubsectionPages;
                    currentSubsubsection = currentSubsubsection->next;
                }

                // Cập nhật tổng số trang của Subsection
                currentSubsection->totalPages = subsectionPages;
                sectionPages += subsectionPages;
                currentSubsection = currentSubsection->next;
            }

            // Cập nhật tổng số trang của Section
            currentSection->totalPages = sectionPages;
            chapterPages += sectionPages;
            currentSection = currentSection->next;
        }

        // Cập nhật tổng số trang của Chapter
        currentChapter->totalPages = chapterPages;
        totalPages += chapterPages;
        currentChapter = currentChapter->next;
    }

    // Cập nhật tổng số trang của Book
    my_book->totalPages = totalPages;
}


// Hàm xác định số chương
int countChapters(book my_book) {
    int count = 0;
    chapter current = my_book->head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Hàm tìm chương dài nhất theo tổng số trang
chapter findLongestChapterByPages(book my_book) {
    chapter longest = nullptr;
    int maxPages = 0;

    chapter current = my_book->head;
    while (current != nullptr) {
        // Cập nhật tổng số trang của chương hiện tại
        updatePageCountChapter(current);

        if (current->totalPages > maxPages) {
            maxPages = current->totalPages;
            longest = current;
        }
        current = current->next;
    }
    return longest;
}

// Hàm in chi tiết thông tin của sách và các mục
void printBookDetails(book my_book) {
    cout << "Book: " << my_book->name << ", Total Pages: " << my_book->totalPages << endl;
    
    chapter currentChapter = my_book->head;
    while (currentChapter != nullptr) {
        cout << "Chapter: " << currentChapter->name << ", Total Pages: " << currentChapter->totalPages << endl;
        
        section currentSection = currentChapter->head;
        while (currentSection != nullptr) {
            cout << "\tSection: " << currentSection->name << ", Total Pages: " << currentSection->totalPages << endl;
            
            subsection currentSubsection = currentSection->head;
            while (currentSubsection != nullptr) {
                cout << "\t\tSubsection: " << currentSubsection->name << ", Total Pages: " << currentSubsection->totalPages << endl;
                
                subsubsection currentSubsubsection = currentSubsection->head;
                while (currentSubsubsection != nullptr) {
                    int subsubsectionPages = currentSubsubsection->page_R - currentSubsubsection->page_L + 1;
                    cout << "\t\t\tSubsubsection: " << currentSubsubsection->name 
                         << ", Pages: " << subsubsectionPages << endl << endl;
                    currentSubsubsection = currentSubsubsection->next;
                }
                currentSubsection = currentSubsection->next;
            }
            currentSection = currentSection->next;
        }
        currentChapter = currentChapter->next;
    }
}

// Hàm tìm và xóa Subsubsection
bool findAndDeleteSubsubsection(subsection my_subsection, const string& name) {
    subsubsection current = my_subsection->head;
    subsubsection prev = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (prev == nullptr) {
                my_subsection->head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            updatePageCountSubsection(my_subsection);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Hàm tìm và xóa Subsection
bool findAndDeleteSubsection(section my_section, const string& name) {
    subsection current = my_section->head;
    subsection prev = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (prev == nullptr) {
                my_section->head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            updatePageCountSection(my_section);
            return true;
        }

        // Tìm và xóa trong Subsubsection
        if (findAndDeleteSubsubsection(current, name)) {
            updatePageCountSection(my_section);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Hàm tìm và xóa Section
bool findAndDeleteSection(chapter my_chapter, const string& name) {
    section current = my_chapter->head;
    section prev = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (prev == nullptr) {
                my_chapter->head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            updatePageCountChapter(my_chapter);
            return true;
        }

        // Tìm và xóa trong Subsection
        if (findAndDeleteSubsection(current, name)) {
            updatePageCountChapter(my_chapter);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Hàm tìm và xóa Chapter
bool findAndDeleteChapter(book my_book, const string& name) {
    chapter current = my_book->head;
    chapter prev = nullptr;

    while (current != nullptr) {
        if (current->name == name) {
            if (prev == nullptr) {
                my_book->head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            updatePageCountBook(my_book);
            return true;
        }

        // Tìm và xóa trong Section
        if (findAndDeleteSection(current, name)) {
            updatePageCountBook(my_book);
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Hàm tìm và xóa
bool findAndDelete(book my_book, const string& name) {
    return findAndDeleteChapter(my_book, name);
}

    int main() {
        book myBook = new Book("My Book");
    
        myBook->head = new Chapter("Chapter 1");
        myBook->head->head = new Section("Section 1.1");
        myBook->head->head->head = new Subsection("Subsection 1.1.1");
        myBook->head->head->head->head = new Subsubsection("Subsubsection 1.1.1.1", 1, 5);
        myBook->head->head->head->next = new Subsection("Subsection 1.1.2");
        myBook->head->head->head->next->head = new Subsubsection("Subsubsection 1.1.2.1", 1, 9);
        
        myBook->head->next = new Chapter("Chapter 2");
        myBook->head->next->head = new Section("Section 2.1");
        myBook->head->next->head->head = new Subsection("Subsection 2.1.1");
        myBook->head->next->head->head->head = new Subsubsection("Subsubsection 2.1.1.1", 1, 10);
        
        myBook->head->next->next = new Chapter("Chapter 3");
        myBook->head->next->next->head = new Section("Section 3.1");
        myBook->head->next->next->head->head = new Subsection("Subsection 3.1.1");
        myBook->head->next->next->head->head->head = new Subsubsection("Subsubsection 3.1.1.1", 1, 20);
    
        updatePageCountBook(myBook);
        // In ra thông tin của sách
        cout << "Book details:" << endl;
        printBookDetails(myBook);
    
        // Số chương của sách
        cout << "Number of chapters: " << countChapters(myBook) << endl;
    
        // Tìm chương dài nhất theo số trang
        chapter longestChapter = findLongestChapterByPages(myBook);
        if (longestChapter != nullptr) {
            cout << "Longest chapter: " << longestChapter->name << " with " << longestChapter->totalPages << " pages." << endl;
        } else {
            cout << "No chapters found." << endl;
        }
    
        // Tìm và xóa mục
        string target = "Subsection 1.1.1";
        if (findAndDelete(myBook, target)) {
            cout << "Deleted: " << target << endl;
            updatePageCountBook(myBook);
            // Tổng số trang của sách sau khi xóa
            cout << "Updated total pages of the book: " << myBook->totalPages << endl;

            // In ra thông tin của sách sau khi xóa
            cout << "\nBook details after deletion:" << endl;
            printBookDetails(myBook);
        }
        else 
            cout << "Item not found: " << target << endl;
    
        return 0;
    }
