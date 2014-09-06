#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void showmovies(Item item);
void showmovies_my(const List *plist);

int main(void)
{
  List movies;
  Item temp;

  InitializeList(&movies);
  if(ListIsFull(&movies)){
    printf("No memory available! Bye!\n");
    exit(100);
  }

  puts("Enter first movie title:");
  while(gets(temp.title) != NULL && temp.title[0] != '\0'){
    puts("Enter your rating <0-10>: ");
    scanf("%d", &temp.rating);
    while(getchar() != '\n')
      continue;
    if(AddItem(temp, &movies) == false){
      printf("Problem allocating memory\n");
      break;
    }
    if(ListIsFull(&movies)){
      puts("The list is now full.");
      break;
    }
    puts("Enter next movie title (empty line to stop): ");
  }

  if(ListIsEmpty(&movies))
    printf("No data entered. ");
  else{
    printf("Here is the movies list: \n");
    //Traverse(&movies, showmovies);
    showmovies_my(&movies);
  }

  printf("You entered %d movies.\n", ListItemCount(&movies));

  EmptyTheList(&movies);
  printf("Bye.\n");

  getchar();
  return 0;
}


  void showmovies(Item item){
    printf("Movies: %s, Rating: %d\n", item.title, item.rating);
  }

  void showmovies_my(const List *plist){
    Node *pnode = *plist;
    while(pnode != NULL){
      showmovies(pnode->item);
      pnode = pnode->next;
    }
  }
