#include <stdio.h>

struct Activity {
    int start, finish;
};

void swap(struct Activity *a, struct Activity *b) {
    struct Activity temp = *a;
    *a = *b;
    *b = temp;
}

void sortByFinishTime(struct Activity arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].finish > arr[j + 1].finish) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void activitySelection(struct Activity arr[], int n) {
    sortByFinishTime(arr, n);

    printf("\nSelected activities (by index):\n");
    int i = 0;
    printf("Activity 1 (Start: %d, Finish: %d)\n", arr[i].start, arr[i].finish);

    for (int j = 1; j < n; j++) {
        if (arr[j].start >= arr[i].finish) {
            printf("Activity %d (Start: %d, Finish: %d)\n", j + 1, arr[j].start, arr[j].finish);
            i = j;
        }
    }
}

int main() {
    int n;
    printf("Enter number of activities: ");
    scanf("%d", &n);

    struct Activity arr[n];
    printf("Enter start and finish times of activities:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].finish);
    }

    activitySelection(arr, n);

    return 0;
}