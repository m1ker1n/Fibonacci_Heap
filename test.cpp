#include "pch.h"
#include "Fib_heap.h"

TEST(Heap, Init) {
	Heap_t* h = Init_Heap();
	EXPECT_TRUE(Display_Root_List(h) == 0);
}

TEST(Heap, NullInit) {
	Heap_t* h = NULL;
	EXPECT_TRUE(Display_Root_List(h) == -1);
}

TEST(Heap, OneNode) {
	Heap_t* h = Init_Heap();
	Fib_Heap_Insert(h, 1);
	EXPECT_TRUE(Display_Root_List(h) == 1);
}

TEST(Heap, InsertEightNodes) {
	Heap_t* h = Init_Heap();
	for (int i = 1; i <= 8;i++) {
		Fib_Heap_Insert(h, i);
	}
	EXPECT_TRUE(Display_Root_List(h) == 8);
	EXPECT_TRUE(h->min->key == 1);
}

TEST(Heap, NineNodesExtract) {
	Heap_t* h = Init_Heap();
	for (int i = 1; i <= 9;i++) {
		Fib_Heap_Insert(h, i);
	}
	EXPECT_TRUE(Display_Root_List(h) == 9);
	EXPECT_TRUE(h->min->key == 1);

	for (int i = 1;i <= 9;i++) {
		EXPECT_TRUE(Fib_Heap_Extract_Min_Key(h) == i);
		EXPECT_TRUE(Display_Root_List(h) == 9 - i);
	}
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}