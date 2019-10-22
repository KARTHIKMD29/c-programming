
int printTriangle(int size) {
  int star_count = 0;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j <= i; j++) {
      printf("*");
      star_count++;
    }
    printf("\n");
  }
  return star_count;
}

int main(void) {
  int numStars;
  printf("Here is a triangle with height 4\n");
  numStars = printTriangle(4);
  printf("That triangle had %d total stars\n", numStars);
  printf("Here is a triangle with height 7\n");
  numStars = printTriangle(7);
  printf("That triangle had %d total stars\n", numStars);
  return 0;
}



