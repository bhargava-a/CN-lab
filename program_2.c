#include <stdio.h>

#define INF 99  // Define a constant for infinity

struct rtable {
    int dist[20], nextnode[20];
} table[20];

int cost[20][20], n;

void distvector() {
    int i, j, k, count = 0;

    // Initialize the distance and nextnode tables
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            table[i].dist[j] = cost[i][j];
            table[i].nextnode[j] = j;
        }
    }

    // Distance vector calculation using Bellman-Ford logic
    do {
        count = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                for (k = 0; k < n; k++) {
                    if (table[i].dist[j] > cost[i][k] + table[k].dist[j]) {
                        table[i].dist[j] = table[i].dist[k] + table[k].dist[j];
                        table[i].nextnode[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);
}

int main() {
    int i, j;

    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter the cost matrix (use %d for infinity):\n", INF);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    distvector();

    // Display the distance table for each router
    for (i = 0; i < n; i++) {
        printf("\nState value for router %c\n", i + 65);
        printf("\nDestnode\tNextnode\tDistance\n");

        for (j = 0; j < n; j++) {
            if (table[i].dist[j] == INF)
                printf("%c\t\t-\t\t infinite\n", j + 65);
            else
                printf("%c\t\t%c\t\t%d\n", j + 65, table[i].nextnode[j] + 65, table[i].dist[j]);
        }
    }

    return 0;
}
