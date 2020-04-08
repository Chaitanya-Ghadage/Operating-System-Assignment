#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define debugi(x) printf("DEBUG : %d\n", x)
#define FORN(i, n) for(__typeof(i) i = 0; i < n; i++)

typedef long long ll;

int random_flag = 0; //false
void showInputs(ll *memory_pages, ll number_of_pages, ll number_of_frames);
void drawLine();
int findPageHit(ll *frame_list, ll number_of_frames, ll target)
{
    for(int i = 0; i < number_of_frames; i++)
    {
        if(frame_list[i] == target)
            return 1;
    }
    return 0;
}

void populatePages(ll *memory_pages, ll number_of_pages)
{
    // debugi(no_of_pages);
    for (int i = 0; i < number_of_pages; i++)
        memory_pages[i] = (rand() % 10);
}
int main(int argc, const char **argv)
{
    srand(time(NULL));
    ll number_of_pages;
    ll *memory_pages;
    if(argc == 1)
    {
        printf("enter number of pages in virtual memory ");
        scanf("%lld", &number_of_pages);
        memory_pages = (ll *)malloc(sizeof(ll) * number_of_pages);
        populatePages(memory_pages, number_of_pages);
        random_flag = 1; //true
    }
    else
    {
        number_of_pages = argc - 1;
        memory_pages = (ll *)malloc(sizeof(ll) * number_of_pages);
        int index = 0;
        for(int i = 1; i < argc; i++)
            memory_pages[index++] = atoll(argv[i]);
    }
    ll number_of_frames;
    printf("enter the number of frames ");
    scanf("%lld", &number_of_frames);
    showInputs(memory_pages, number_of_pages, number_of_frames);
    ll *frame_list = (ll *)malloc(number_of_frames * sizeof(ll));
    memset(frame_list, -1, number_of_frames * sizeof(ll));

    ll count_page_hit, count_page_fault;
    count_page_hit = count_page_fault = 0;
    
    ll last = -1;
    for(int i = 0; i < number_of_pages; i++)
    {
        if(findPageHit(frame_list, number_of_frames,memory_pages[i]))
            count_page_hit++;
        else
        {
            frame_list[++last % number_of_frames] = memory_pages[i];
            count_page_fault++;
        }
    }

    printf("No. of Page hits are %lld\n", count_page_hit);
    printf("No. of Page faults are %lld\n", count_page_fault);
    return 0;
}

void showInputs(ll *memory_pages, ll number_of_pages, ll number_of_frames)
{
    printf("You have enter the following data.");
    drawLine();
    printf("Number of pages\t\t\t: %lld\n", number_of_pages);
    if(random_flag) printf("Random ");
    else            printf("Custom ");
    printf("Virtual Memory Pages \t: ");
    for(int i = 0; i < number_of_pages; i++)
        printf("%lld ",memory_pages[i]);
    printf("\nNumber of frames\t\t: %lld", number_of_frames);
    drawLine();
}
void drawLine()
{
    printf("\n");
    for(int i = 0; i < 30; i++)
        printf("-");
    printf("\n");
}
