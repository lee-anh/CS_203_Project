CC=gcc

OBJS = ArrayList.o BinaryTree.o BTCity.o CityIndex.o CostIndex.o FileReader.o FileWriter.o Indexor.o IntArray.o LinkedList.o NewController.o restaurant.o TimeIndex.o main.o

all: $(OBJS) 
	
	$(CC) *.o -o p2

clean: 
	rm ./p2
	rm *.o

ArrayList.o: ArrayList.c ArrayList.h restaurant.h
	$(CC) -c ArrayList.c

BinaryTree.o: BinaryTree.c BinaryTree.h restaurant.h LinkedList.h ArrayList.h
	$(CC) -c BinaryTree.c

BTCity.o: BTCity.c BTCity.h restaurant.h LinkedList.h
	$(CC) -c BTCity.c

CityIndex.o: CityIndex.c CityIndex.h IntArray.h restaurant.h LinkedList.h
	$(CC) -c CityIndex.c

CostIndex.o: CostIndex.c CostIndex.h LinkedList.h restaurant.h
	$(CC) -c CostIndex.c

FileReader.o: FileReader.c FileReader.h restaurant.h BinaryTree.h
	$(CC) -c FileReader.c

FileWriter.o: FileWriter.c FileWriter.h restaurant.h BinaryTree.h LinkedList.h ArrayList.h
	$(CC) -c FileWriter.c

Indexor.o: Indexor.c Indexor.h LinkedList.h restaurant.h BinaryTree.h CostIndex.h CityIndex.h TimeIndex.h BTCity.h
	$(CC) -c Indexor.c

IntArray.o: IntArray.c IntArray.h 
	$(CC) -c IntArray.c

LinkedList.o: LinkedList.c LinkedList.h restaurant.h ArrayList.h
	$(CC) -c LinkedList.c

NewController.o: NewController.c NewController.h restaurant.h FileReader.h FileWriter.h BinaryTree.h Indexor.h
	$(CC) -c NewController.c

restaurant.o: restaurant.c restaurant.h 
	$(CC) -c restaurant.c

TimeIndex.o: TimeIndex.c TimeIndex.h IntArray.h restaurant.h LinkedList.h 
	$(CC) -c TimeIndex.c

main.o: main.c NewController.h
	$(CC) -c main.c

