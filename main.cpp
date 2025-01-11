#include<iostream>
#include<fstream>
using namespace std;

class Profile;
class Page;
class Users;
class MyApp;
class Post;
class Date;
class Activity;
class Comment;
class Memory;

class Helper
{
public:
	static int StringLenght(const char* str)
	{
		int length = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			length++;
		}
		return length;

	}
	static void StringCopy(char*& dest, const char*& src) {
		int i;
		for (i = 0; src[i] != '\0'; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(const char* str)
	{
		int stringLength = StringLenght(str);

		char* string = 0;

		if (stringLength > 0)
		{
			string = new char[stringLength + 1];
			int a;
			Helper::StringCopy(string, str);
		}
		return string;

	}
	static bool searchString(char* ptr, const  char* str)
	{
		bool flag = false;
		for (int i = 0; ptr[i] != '\0'; i++)
		{
			if (ptr[i] == str[0])
			{
				flag = true;

				for (int j = 0; str[j] != '\0'; j++, i++)
				{
					if (str[j] != ptr[i])
					{
						flag = false;
					}
				}
				break;
			}
		}
		return flag;
	}
};

//////////////////////////////////////////////////////////// 

class Profile
{
protected:
	char* ID;
	Post** timeLine;
	int numOfPosts;
public:
	Profile();
	virtual ~Profile();
	virtual void AddPostToTimeLine(Post* Id) = 0;
	virtual void PrintProfileName()=0;
	virtual void View()=0;
	virtual void PrintInfo()=0;
	virtual bool WasPostedEarlier(Post*)=0;
	virtual void AddMemory(Memory*)=0;
	virtual void DisplayMemories()=0;
};
Profile::Profile()
{
	ID = 0;
	timeLine = 0;
}
Profile::~Profile()
{
	if (ID)
	{
		delete[] ID;
	}
	//Deallocating Posts
	for (int i = 0; i < numOfPosts; i++)
	{
		delete timeLine[i];
	}
	if (numOfPosts)
	{
		delete[] timeLine;
	}
}


//////////////////////////////////////////////////////////// 

class Date
{
public:
	int day;
	int month;
	int year;
	static Date currentDate;
public:
	Date();
	~Date();
	void SetDate(int, int, int);
	static void SetCurrentDate(int, int, int);
	void ReadDate(ifstream&);
	void Display();
	bool CompareWithcurrentdate();
	int GiveYearDifference(Date);
	bool IsDateAndMonthEqual();
};
Date Date::currentDate;
Date::Date()
{
	day = 0;
	month = 0;
	year = 0;
}
Date::~Date()
{

}
void Date::SetDate(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}
void Date::SetCurrentDate(int d, int m, int y)
{
	currentDate.day = d;
	currentDate.month = m;
	currentDate.year = y;
}
void Date::ReadDate(ifstream& fin)
{
	fin >> day;
	fin >> month;
	fin >> year;
}
void Date::Display()
{
	cout << "(" << day << ", " << month << ", " << year << ")";
}
bool Date::CompareWithcurrentdate()
{
	if (this->year == currentDate.year)
	{
		if (this->day == currentDate.day || this->day == (currentDate.day) - 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Date::IsDateAndMonthEqual()
{
	if (currentDate.month == this->month)
	{
		if (currentDate.day == this->day)
		{
			return true;
		}
	}
	return false;
}
int Date::GiveYearDifference(Date date)
{
	int yearDifference = date.year - this->year;
	return yearDifference;
}

////////////////////////////////////////////////////////////

class Activity
{
	int Type;
	char* value;
public:
	Activity();
	~Activity();
	void LoadDataFromFile(ifstream&);
	void SetActivity(int, char*);
	void PrintValue();
	void DisplayActivity();
};
Activity::Activity()
{
	Type = 0;
	value = 0;
}
Activity::~Activity()
{
	if (value)
	{
		delete[] value;
	}
}
void Activity::LoadDataFromFile(ifstream& file)
{
	char temp[100];
	int typ;
	file >> typ;
	file.getline(temp, 100);
	//file.ignore(100, '\n');
	SetActivity(typ, temp);
}
void Activity::SetActivity(int typ, char* description)
{
	Type = typ;
	if (description)
	{
		value = Helper::GetStringFromBuffer(description);
	}
}
void Activity::PrintValue()
{
	if (value)
	{
		for (int i = 0; value[i] != '\0'; i++)
		{
			cout << value[i];
		}
	}
}
void Activity::DisplayActivity()
{
	switch (Type)
	{
	case 1:
		cout << " feeling ";
		break;
	case 2:
		cout << " is thinking about ";
		break;
	case 3:
		cout << " is making ";
		break;
	case 4:
		cout << " is celebrating ";
		break;
	}

	this->PrintValue();

}

//////////////////////////////////////////////////////////// 

class Comment
{
private:
	char* ID;
	Profile* CommentBy;
	char* ActualComment;
public:
	Comment();
	~Comment();
	void SetComment(char*, char*, Profile*);
	void Display();
};
Comment::Comment()
{
	ID = 0;
	CommentBy = 0;
	ActualComment = 0;
}
Comment::~Comment()
{
	//deallocating
	if (ID)
	{
		delete[] ID;
	}

	if (CommentBy)
	{
		CommentBy = 0;
	}
	if (ActualComment)
	{
		delete[] ActualComment;
	}
}
void Comment::SetComment(char* id, char* txt, Profile* by)
{
	ID = Helper::GetStringFromBuffer(id);
	ActualComment = Helper::GetStringFromBuffer(txt);
	CommentBy = by;
}
void Comment::Display()
{
	cout << "               ";
	CommentBy->PrintProfileName();
	cout << " wrote : \"" << ActualComment << "\"";
}

//////////////////////////////////////////////////////////// 

class Post
{
private:
	char* ID;
	char* Text;
	Date SharedDate;
	Activity* activity;
	Profile* SharedBy;
	Comment** commentsList;
	Profile** likedBy;
	int numOfLikes;
	int numOfComments;
public:
	Post();
	~Post();
	void SetWhoPosted(Profile*);
	char* GetPostId();
	Date GetPostingDate();
	void PrintNameWhoShared();
	void AddLike(Profile*);
	void LoadDataFromFile(ifstream&);
	void AddComment(Comment*);
	virtual void ShowPost();
	void ShowPostdata();
	void DisplayOnHome();
	void DisplayIfRecent();
	void DisplayLikedList();
	void DisplayIfItIsMemory();

};
Post::Post()
{
	ID = 0;
	Text = 0;
	activity = 0;
	SharedBy = 0;
	commentsList = 0;
	likedBy = 0;
	numOfLikes = 0;
	numOfComments = 0;

}
Post::~Post()
{
	//Deallocating ID
	if (ID)
	{
		delete[] ID;
	}
	//Deallocating Text
	if (Text)
	{
		delete[] Text;
	}
	//Deallocating activity
	if (activity)
	{
		delete[]activity;
	}
	//Deallocating commentList
	for (int i = 0; i < numOfComments; i++)
	{
		delete commentsList[i];
	}
	if (numOfComments)
	{
		delete[] commentsList;
	}
	//Deallocating commentList
	for (int i = 0; i < numOfLikes; i++)
	{
		likedBy[i] = 0;
	}
	if (numOfLikes)
	{
		delete[] likedBy;
	}
}
void Post::SetWhoPosted(Profile* person)
{
 	SharedBy = person;
}
char* Post::GetPostId()
{
	return ID;
}
Date Post::GetPostingDate()
{
	return SharedDate;
}
void Post::PrintNameWhoShared()
{
	SharedBy->PrintProfileName();
}
void Post::AddLike(Profile* Id)
{
	numOfLikes++;
	if (!likedBy)
	{
		likedBy = new Profile * [numOfLikes];
		likedBy[0] = Id;
	}
	else
	{
		Profile** temp = new Profile * [numOfLikes];
		for (int i = numOfLikes - 2; i >= 0; i--)
		{
			temp[i] = likedBy[i];
		}
		temp[numOfLikes - 1] = Id;
		for (int i = 0; i < numOfLikes - 1; i++)
		{
			//delete[] likedBy[i];
		}
		delete[] likedBy;
		likedBy = temp;
		temp = 0;
	}

}
void Post::LoadDataFromFile(ifstream& file)
{
	int type;
	char temp[100];
	file >> type;
	file >> temp;
	ID = Helper::GetStringFromBuffer(temp);
	SharedDate.ReadDate(file);
	file.getline(temp, 100);
	file.getline(temp, 100);
	//file.ignore(100, '\n');
	Text = Helper::GetStringFromBuffer(temp);
	if (type == 2)
	{
		activity = new Activity;
		activity->LoadDataFromFile(file);
	}
}
void Post::AddComment(Comment* cmnt)
{
	if (numOfComments != 10)
	{
		numOfComments++;
		if (!commentsList)
		{
			commentsList = new Comment * [numOfComments];
			commentsList[0] = cmnt;
		}
		else
		{
			Comment** temp = new Comment * [numOfComments];
			for (int i = numOfComments - 2; i >= 0; i--)
			{
				temp[i] = commentsList[i];
			}
			temp[numOfComments - 1] = cmnt;
			for (int i = 0; i < numOfComments - 1; i++)
			{
				//delete[] commentsList[i];
			}
			delete[] commentsList;
			commentsList = temp;
			temp = 0;
		}
	}
	else
	{
		cout << "\nComment box is already full.\n\n";
	}
}
void Post::ShowPost()
{
	cout << "-";
	SharedBy->PrintProfileName();

	if (activity)
	{
		activity->DisplayActivity();
	}
	cout << "...";
	SharedDate.Display();
	cout << endl;
	cout << "   \"" << Text << "...\"" << endl;
	for (int i = 0; i < numOfComments; i++)
	{
		commentsList[i]->Display();
		cout << endl;
	}
	cout << endl << endl;
}
void Post::ShowPostdata()
{
	cout << "-";
	SharedBy->PrintProfileName();

	if (activity)
	{
		activity->DisplayActivity();
	}
	cout << "...";
	SharedDate.Display();
	cout << endl;
	cout << "   \"" << Text << "...\"" << endl;
}
void Post::DisplayOnHome()
{
	SharedBy->PrintProfileName();
	if (activity)
	{
		activity->DisplayActivity();
		cout << endl;
	}
	else
	{
		cout << " shared ";
	}
	cout << " \"" << Text << "...\"" << endl;
	for (int i = 0; i < numOfComments; i++)
	{
		commentsList[i]->Display();
		cout << endl;
	}
	cout << endl << endl;
}
void Post::DisplayIfRecent()
{
	if (SharedDate.CompareWithcurrentdate())
	{
		DisplayOnHome();
	}
}
void Post::DisplayLikedList()
{
	if (numOfLikes)
	{
		cout << "\nPost liked by : \n\n";
		for (int i = 0; i < numOfLikes; i++)
		{
			likedBy[i]->PrintInfo();
			cout << endl;
		}
	}
	else
	{
		cout << "\n\nNolike yet.\n\n";
	}
}
void Post::DisplayIfItIsMemory()
{
	int yearDiff = SharedDate.GiveYearDifference(Date::currentDate);
	if (yearDiff)
	{
		if (SharedDate.IsDateAndMonthEqual())
		{
			cout << "On this Day\n";
			cout << yearDiff;
			if (yearDiff == 1)
			{
				cout << " year ago\n\n";
			}
			else
			{
				cout << " years ago\n\n";
			}
			ShowPost();
		}
	}
}

////////////////////////////////////////////////////////////

class Memory :public Post
{
private:
	Post* ActualPost;
	char* description;
	Date sharingDate;
	int yearDifference;
public:
	Memory(Post*, const char*);
	~Memory();
	void ShowPost();
};
Memory::Memory(Post* pst, const char* txt)
{
	ActualPost = pst;
	description = Helper::GetStringFromBuffer(txt);
	sharingDate = Date::currentDate;
}
Memory::~Memory()
{
	if (ActualPost)
	{
		ActualPost = 0;
	}
	if (description)
	{
		delete[] description;
	}
}
void Memory::ShowPost()
{
	cout << "~~~";
	ActualPost->PrintNameWhoShared();
	cout << " shared a memory~~~...";
	sharingDate.Display();
	cout << "\n \"" << description << "\"\n";
	cout << "-";
	yearDifference = ActualPost->GetPostingDate().GiveYearDifference(sharingDate);
	cout << "(";
	if (yearDifference == 0)
	{
		cout << "Earlier this year";
	}
	else if (yearDifference == 1)
	{
		cout << yearDifference << " year ago";
	}
	else
	{
		cout << yearDifference << " years ago";
	}
	cout << ")" << endl;
	ActualPost->ShowPostdata();
	cout << endl << endl;
}

////////////////////////////////////////////////////////////

class Page :public Profile
{
private:
	char* title;
public:
	Page();
	~Page();
	void LoadDataFromFile(ifstream& file);
	char* GetpageID();
	void PrintInfo();
	bool WasPostedEarlier(Post*);
	void AddPostToTimeLine(Post*);
	void AddMemory(Memory*);
	void PrintProfileName();
	void View();
	void DisplayRecentPost();
	void DisplayMemories();
};
Page::Page()
{
 	title = 0;
}
Page::~Page()
{
	//Deallocating title of the page
	if (title)
	{
		delete[] title;
	}
}
char* Page::GetpageID()
{
	return ID;
}
void Page::LoadDataFromFile(ifstream& file)
{
	char str[100];
	file >> str;
	ID = new char[Helper::StringLenght(str) + 1];
	ID = Helper::GetStringFromBuffer(str);
	file.ignore(100, ' ');
	file.getline(str, 100);
	title = new char[Helper::StringLenght(str) + 1];
	title = Helper::GetStringFromBuffer(str);
}
void Page::PrintInfo()
{
	cout << ID << "-" << title;
}
void Page::AddPostToTimeLine(Post* Id)
{
	numOfPosts++;
	if (!(timeLine))
	{
		timeLine = new Post * [numOfPosts];
		timeLine[0] = Id;
	}
	else
	{
		Post** temp = new Post * [numOfPosts];
		for (int i = numOfPosts - 2; i >= 0; i--)
		{
			temp[i] = timeLine[i];
		}
		temp[numOfPosts - 1] = Id;
		for (int i = 0; i < numOfPosts - 1; i++)
		{
			//delete timeLine[i];
		}
		delete[] timeLine;
		timeLine = temp;
		temp = 0;
	}
}
void Page::AddMemory(Memory* memory)
{
	numOfPosts++;
	Post** temp = new Post * [numOfPosts];
	int k = numOfPosts - 1;
	for (int i = numOfPosts - 2; i >= 0; i--)
	{
		temp[k] = timeLine[i];
		k--;
	}
	temp[0] = memory;
	for (int i = 0; i < numOfPosts - 1; i++)
	{
		timeLine[i] = 0;
	}
	delete[] timeLine;
	timeLine = temp;
	temp = 0;
}
void Page::PrintProfileName()
{
	cout << title;
}
bool Page::WasPostedEarlier(Post* post)
{
	for (int i = 0; i < numOfPosts; i++)
	{
		if (Helper::searchString(post->GetPostId(), timeLine[i]->GetPostId()))
		{
			return true;
		}
	}
	return false;
}
void Page::View()
{
	if (numOfPosts)
	{
		for (int i = 0; i < numOfPosts; i++)
		{
			//cout << "-" << title;
			timeLine[i]->ShowPost();
		}
	}
	else
	{
		cout << title << " has not posted anything yet.\n";
	}
}
void Page::DisplayMemories()
{
	if (numOfPosts)
	{
		cout << "\n\nWe hope you enjoy looking back and sharing your memories on Facebook," <<
			"from\nthe most recent to those long ago.\n\n";
		for (int i = 0; i < numOfPosts; i++)
		{
			timeLine[i]->DisplayIfItIsMemory();
		}
	}
}
void Page::DisplayRecentPost()
{
	if (numOfPosts)
	{
		for (int i = 0; i < numOfPosts; i++)
		{
			timeLine[i]->DisplayIfRecent();
		}
	}
}

//////////////////////////////////////////////////////////// 

class User :public Profile
{
private:
	char* firstName;
	char* lastName;
	Page** LikedPagesList;
	User** FriendList;
	int noOfLikedPages;
	int noOfFriends;

public:
	User();
	~User();
	char* GetUserID();
	void PrintName();
	void LoadDataFromFile(ifstream&);
	void LikePage(Page*);
	void AddFriendToTheList(User* ptr);
	void PrintInfo();
	bool WasPostedEarlier(Post*);
	void ShowFriendList();
	void ShowPageList();
	void AddPostToTimeLine(Post* Id);
	void AddMemory(Memory*);
	void PrintProfileName();
	void View();
	void DisplayRecentPost();
	void DisplayHomeOfUser();
	void DisplayMemories();

};
User::User()
{
 	firstName = 0;
	lastName = 0;
	LikedPagesList = new Page * [10];
	LikedPagesList[0] = NULL;
	FriendList = new User * [10];
	FriendList[0] = NULL;
	noOfFriends = 0;
	noOfLikedPages = 0;
 }
User::~User()
{
	//Deallocation of LikedPages
	for (int i = 0; i < noOfLikedPages; i++)
	{
		LikedPagesList[i] = 0;
	}
	if (noOfLikedPages)
	{
		delete[] LikedPagesList;
	}
	//Deallocation of FriendList
	for (int i = 0; i < noOfFriends; i++)
	{
		FriendList[i] = 0;
	}
	if (noOfFriends)
	{
		delete[] FriendList;
	}
	//Deallocation of firstname
	if (firstName)
	{
		delete[] firstName;
	}
	//Deallocation of lastName
	if (lastName)
	{
		delete[] lastName;
	}
}
char* User::GetUserID()
{
	return ID;
}
void User::PrintName()
{
	cout << firstName << " " << lastName;
}
void User::LoadDataFromFile(ifstream& file)
{
	char temp[50];
	file >> temp; //Reading userID from file
	ID = new char[Helper::StringLenght(temp) + 1];
	ID = Helper::GetStringFromBuffer(temp);
	file >> temp;//Reading firstname of the user
	firstName = new char[Helper::StringLenght(temp) + 1];
	firstName = Helper::GetStringFromBuffer(temp);
	file >> temp;//reading last name of the user
	lastName = new char[Helper::StringLenght(temp) + 1];
	lastName = Helper::GetStringFromBuffer(temp);
}
void User::LikePage(Page* ptr)
{
	if (noOfLikedPages != 10)
	{
		for (int i = 0; i < 10; i++)
		{
			if (LikedPagesList[i] == NULL)
			{
				LikedPagesList[i] = ptr;
				if (i != 9)
				{
					LikedPagesList[i + 1] = NULL;
				}
				noOfLikedPages++;
				break;
			}
		}
	}
	else
	{
		cout << "\nLiked pages limit reached.\n\n";
	}
}
void User::AddFriendToTheList(User* ptr)
{
	if (noOfFriends != 10)
	{
		for (int i = 0; i < 10; i++)
		{
			if (FriendList[i] == NULL)
			{
				FriendList[i] = ptr;
				if (i != 9)
				{
					FriendList[i + 1] = NULL;
				}
				noOfFriends++;
				break;
			}
		}
	}
	else
	{
		cout << "\nFriend List is full, can't add more.\n\n";
	}
}
void User::PrintInfo()
{
	cout << ID << "- " << firstName << " " << lastName;
}
bool User::WasPostedEarlier(Post* post)
{
	for (int i = 0; i < numOfPosts; i++)
	{
		if (Helper::searchString(post->GetPostId(), timeLine[i]->GetPostId()))
		{
			return true;
		}
	}
	return false;
}
void User::PrintProfileName()
{
	cout << firstName << " " << lastName;
}
void User::AddMemory(Memory* memory)
{
	numOfPosts++;
	Post** temp = new Post * [numOfPosts];
	int k = numOfPosts - 1;
	for (int i = numOfPosts - 2; i >= 0; i--)
	{
		temp[k] = timeLine[i];
		k--;
	}
	temp[0] = memory;
	for (int i = 0; i < numOfPosts - 1; i++)
	{
		timeLine[i] = 0;
	}
	delete[] timeLine;
	timeLine = temp;
	temp = 0;
}
void User::ShowFriendList()
{
	if (FriendList[0] == NULL)
	{
		cout << "USER IS SO UNSOCIAL, HE HAS NO FRIEND\n";
	}
	else
	{
		for (int i = 0; FriendList[i] != NULL; i++)
		{
			FriendList[i]->PrintInfo();
			cout << endl;
		}
	}
}
void User::ShowPageList()
{
	if (LikedPagesList[0] == NULL)
	{
		cout << "USER HAS NOT LIKED ANY PAGE\n";
	}
	else
	{
		for (int i = 0; LikedPagesList[i] != NULL; i++)
		{
			LikedPagesList[i]->PrintInfo();
			cout << endl;
		}
	}
}
void User::AddPostToTimeLine(Post* Id)
{
	numOfPosts = numOfPosts + 1;
	if (!timeLine)
	{
		timeLine = new Post * [numOfPosts];
		timeLine[0] = Id;
	}
	else
	{
		Post** temp = new Post * [numOfPosts];
		for (int i = numOfPosts - 2; i >= 0; i--)
		{
			temp[i] = timeLine[i];
		}
		temp[numOfPosts - 1] = Id;
		for (int i = 0; i < numOfPosts - 1; i++)
		{
			//delete[] timeLine[i];
		}
		delete[] timeLine;
		timeLine = temp;
		temp = 0;
	}
}
void User::View()
{
	if (numOfPosts)
	{
		for (int i = 0; i < numOfPosts; i++)
		{
			timeLine[i]->ShowPost();
		}
	}
	else
	{
		PrintName();
		cout << " has not posted anything yet.\n";
	}
}
void User::DisplayRecentPost()
{
	if (numOfPosts)
	{
		for (int i = 0; i < numOfPosts; i++)
		{
			timeLine[i]->DisplayIfRecent();
		}
	}
}
void User::DisplayHomeOfUser()
{
	PrintName();
	cout << " Home Page\n\n";
	for (int i = 0; i < noOfFriends; i++)
	{
		FriendList[i]->DisplayRecentPost();
	}
	for (int i = 0; i < noOfLikedPages; i++)
	{
		LikedPagesList[i]->DisplayRecentPost();
	}
}
void User::DisplayMemories()
{
	if (numOfPosts)
	{
		cout << "\n\nWe hope you enjoy looking back and sharing your memories on Facebook," <<
			"from\nthe most recent to those long ago.\n\n";
		for (int i = 0; i < numOfPosts; i++)
		{
			timeLine[i]->DisplayIfItIsMemory();
		}
	}
}

/////////////////////////////////////////////////////////// 

class MyApp
{
private:
	Page** page;
	User** user;
	Post** post;
	Comment** comment;
	static int TotalPages;
	static int TotalUsers;
	static int TotalPosts;
	static int TotalComments;

public:
	MyApp();
	~MyApp();
	void Load();
	void LoadPagesFromFile();
	void LoadUsersFromFile();
	void LoadPostsFromFile();
	void LoadCommentsFromFile();
	Page* SearchPageByID(const char*);
	User* SearchUserByID(const char*);
	Profile* SearchObjectById(const char*);
	Post* SearchPostById(const char*);
	void WriteCommentOnPost(const char*, const char*, const char*);
	void LikeAPost(const char*, const char*);
	void shareMemory(const char*, const char*, const char*);
	void Operate();
};
int MyApp::TotalPages = 0;
int MyApp::TotalPosts = 0;
int MyApp::TotalUsers = 0;
int MyApp::TotalComments = 0;

MyApp::MyApp()
{
	page = 0;
	user = 0;
	post = 0;
	comment = 0;
}
MyApp::~MyApp()
{
	for (int i = 0; i < TotalPages; i++)
	{
		delete page[i];
	}
	if (page)
	{
		delete[] page;
	}
	for (int i = 0; i < TotalUsers; i++)
	{
		delete user[i];
	}
	if (user)
	{
		delete[] user;
	}
	if (post)
	{
		delete post;
	}
	if (comment)
	{
		delete[] comment;
	}
}
void MyApp::Load()
{
	LoadPagesFromFile();
	LoadUsersFromFile();
	LoadPostsFromFile();
	LoadCommentsFromFile();
}
Page* MyApp::SearchPageByID(const char* str)
{
	bool found = false;
	int total = MyApp::TotalPages;
	for (int i = 0; i < total; i++)
	{
		found = Helper::searchString(page[i]->GetpageID(), str);
		if (found)
		{
			return page[i];
		}
	}
	return NULL;
}
User* MyApp::SearchUserByID(const char* str)
{
	bool flag = false;
	for (int i = 0; i < 20; i++)
	{
		flag = Helper::searchString(user[i]->GetUserID(), str);
		if (flag)
		{
			return user[i];
		}
	}
	return NULL;
}
Profile* MyApp::SearchObjectById(const char* str)
{
 	if (str[0] == 'u')
	{
		return SearchUserByID(str);
	}
	else
	{
		return SearchPageByID(str);
	}
 }
Post* MyApp::SearchPostById(const char* str)
{
	bool flag = false;
	for (int i = 0; i < TotalPosts; i++)
	{
		flag = Helper::searchString(post[i]->GetPostId(), str);
		if (flag)
		{
			return post[i];
		}
	}
	return NULL;
}
void MyApp::WriteCommentOnPost(const char* obj, const char* pst, const char* cmnt)
{
	Profile* object = SearchObjectById(obj);
	if (object)
	{
		Post* post = SearchPostById(pst);
		if (post)
		{
			Comment* comment = new Comment;
			char id[] = { "AA" };
			const char* temp = cmnt;
			char* text;
			text = Helper::GetStringFromBuffer(cmnt);
			comment->SetComment(id, text, object);
			post->AddComment(comment);
		}
		else
		{
			cout << "\nNo post found with entered ID\n\n";
		}
	}
	else
	{
		cout << "\nNo profile found with entered ID\n\n";
	}
}
void MyApp::LikeAPost(const char* obj, const char* pst)
{
	Profile* object = SearchObjectById(obj);
	if (object)
	{
		Post* post = SearchPostById(pst);
		if (post)
		{
			post->AddLike(object);
		}
		else
		{
			cout << "\nNo post found with entered ID\n\n";
		}
	}
	else
	{
		cout << "\nNo profile found with entered ID\n\n";
	}
}
void MyApp::shareMemory(const char* objStr, const char* postStr, const char* txt)
{
	Profile* object = SearchObjectById(objStr);
	if (object)
	{
		Post* post = SearchPostById(postStr);
		if (post)
		{
			if (object->WasPostedEarlier(post))
			{
				Memory* memory;
				memory = new Memory(post, txt);
				object->AddMemory(memory);
			}
		}
		else
		{
			cout << "\nNo Post found with given ID\n\n";
		}
	}
	else
	{
		cout << "\nNo User found with given ID\n\n";
	}
}
void MyApp::LoadPagesFromFile()
{
	ifstream pagesFile("SocialNetworkPages.txt");
	pagesFile >> TotalPages;
	this->page = new Page * [TotalPages];
	for (int i = 0; i < TotalPages; i++)
	{
		page[i] = new Page;
		page[i]->LoadDataFromFile(pagesFile);
	}
}
void MyApp::LoadUsersFromFile()
{
	ifstream usersFile("SocialNetworkUsers.txt");
	usersFile >> TotalUsers;
	this->user = new User * [TotalUsers];
	char*** tempUsers = new char** [TotalUsers];
	for (int i = 0; i < TotalUsers; i++)
	{
		tempUsers[i] = new char* [10];
	}
	for (int i = 0; i < TotalUsers; i++)
	{
		user[i] = new User;
		user[i]->LoadDataFromFile(usersFile);//This function will read ID ,firstName and lastName of the user from the user file.
		char str[10];
		int j = 0;

		////Reading users ID from the file then storing them temporarily in TempUsers Array.
		while (1)
		{
			usersFile >> str;
			if (str[0] == '-')
			{
				break;
			}
			tempUsers[i][j] = new char[3];
			tempUsers[i][j] = Helper::GetStringFromBuffer(str);
			j++;
		}
		tempUsers[i][j] = NULL;

		////Reading page id from file and then adding them in the array of liked pages.
		while (1)
		{
			usersFile >> str;
			if (str[0] == '-')
			{
				break;
			}
			Page* pagePtr = 0;
			pagePtr = SearchPageByID(str);
			if (pagePtr)
			{
				user[i]->LikePage(pagePtr);
			}
		}

	}
	////Reading friends from tempUser array and then adding those friends in the friendList of the users.
	for (int i = 0; i < TotalUsers; i++)
	{
		for (int j = 0; tempUsers[i][j] != NULL; j++)
		{
			User* userPtr = 0;
			userPtr = SearchUserByID(tempUsers[i][j]);
			if (userPtr)
			{
				user[i]->AddFriendToTheList(userPtr);
			}
		}
	}
	////Deallocating memory
	for (int i = 0; i < TotalUsers; i++)
	{
		for (int j = 0; tempUsers[i][j] != NULL; j++)
		{
			delete[] tempUsers[i][j];
		}
		delete[] tempUsers[i];
	}
	delete[]tempUsers;

}
void MyApp::LoadPostsFromFile()
{
	ifstream postFile("SocialNetworkPosts.txt");
	char temp[100];
	postFile >> TotalPosts;
	post = new Post * [TotalPosts];
	for (int i = 0; i < TotalPosts; i++)
	{
		post[i] = new Post;
		post[i]->LoadDataFromFile(postFile);
		postFile >> temp;
		Profile* objPtr = SearchObjectById(temp);
		if (objPtr)
		{
			objPtr->AddPostToTimeLine(post[i]);
			post[i]->SetWhoPosted(objPtr);
		}
		postFile >> temp;
		while (temp[0] != '-')
		{
			Profile* tempObj = SearchObjectById(temp);
			if (tempObj)
			{
				post[i]->AddLike(tempObj);
			}
			postFile >> temp;
		}
	}
}
void MyApp::LoadCommentsFromFile()
{
	char tempId[20];
	char temp[20];
	char text[100];
	ifstream commentFile("SocialNetworkComments.txt");
	commentFile >> TotalComments;
	comment = new Comment * [TotalComments];
	for (int i = 0; i < TotalComments; i++)
	{
		comment[i] = new Comment;
		commentFile >> tempId;
		commentFile >> temp;
		Post* tempPost = SearchPostById(temp);
		tempPost->AddComment(comment[i]);
		commentFile >> temp;
		Profile* commentBy = SearchObjectById(temp);
		commentFile.getline(text, 100);
		//commentFile.getline(text, 100);
		comment[i]->SetComment(tempId, text, commentBy);
	}

}
void MyApp::Operate()
{
	cout << "-----------------------------------------------------------------\n";
	cout << "Command :         Set current System Date 15 11 2017" << endl;
	cout << "-----------------------------------------------------------------\n";
	Date::SetCurrentDate(15, 11, 2017);
	cout << "System Date:            15/11/2017\n\n";

	char userId[] = { "u7" };
	User* currentUser = SearchUserByID(userId);
	if (currentUser)
	{
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :        Set current user to u7" << endl;
		cout << "-----------------------------------------------------------------\n";
		currentUser->PrintName();
		cout << " has been set as a current user.\n\n";
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         View Friend List\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->PrintName();
		cout << "-" << "Friend List\n\n";
		currentUser->ShowFriendList();
		cout << endl << endl;

		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         View Liked Pages\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->PrintName();
		cout << "-" << "Liked Pages\n\n";
		currentUser->ShowPageList();
		cout << endl;
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         View Home\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->DisplayHomeOfUser();
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         View TimeLine\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->View();

		char postId[] = "post5";
		Post* currentPost = SearchPostById(postId);
		if (currentPost)
		{
			cout << "-----------------------------------------------------------------\n";
			cout << "Command :         View Liked List(post 5)\n";
			cout << "-----------------------------------------------------------------\n";
			currentPost->DisplayLikedList();
			cout << "-----------------------------------------------------------------\n";
			cout << "Command :         Like Post(post 5)\n";
			cout << "Command :         View Liked List(post 5)\n";
			cout << "-----------------------------------------------------------------\n";
			LikeAPost(userId, postId);
			currentPost->DisplayLikedList();
			cout << "-----------------------------------------------------------------\n";
			cout << "Command :         Post Comment(post4, How have you spent your holidays?)\n";
			cout << "Command :         View Post(post 4)\n";
			cout << "-----------------------------------------------------------------\n";
			WriteCommentOnPost(userId, "post4", "How have you spent your holidays?");
			currentPost = SearchPostById("post4");
			if (currentPost)
			{
				currentPost->ShowPost();
			}
			cout << "-----------------------------------------------------------------\n";
			cout << "Command :         Post Comment(post8, Thanks for the wishes)\n";
			cout << "Command :         View Post(post 8)\n";
			cout << "-----------------------------------------------------------------\n";
			WriteCommentOnPost(userId, "post8", "Thanks for the wishes");
			currentPost = SearchPostById("post8");
			if (currentPost)
			{
				currentPost->ShowPost();
			}
		}
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         SeeYourMemories()\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->DisplayMemories();
		cout << "-----------------------------------------------------------------\n";
		cout << "Command : ShareMemory(post10, Never thought I will be specialist in this field...)\n";
		cout << "Command :          View TimeLine\n";
		cout << "-----------------------------------------------------------------\n";
		shareMemory(userId, "post10", "Never thought I will be specialist in this field...");
		currentUser->View();
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :          ViewPage(p1)\n";
		cout << "-----------------------------------------------------------------\n";
		char pageId[] = "p1";
		Page* currentPage = SearchPageByID(pageId);
		if (currentPage)
		{
			currentPage->View();
		}
	}
	currentUser = SearchUserByID("u11");
	if (currentUser)
	{
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :        Set current user to u11" << endl;
		cout << "-----------------------------------------------------------------\n";
		currentUser->PrintName();
		cout << " has been set as a current user.\n\n";
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         View Home\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->DisplayHomeOfUser();
		cout << "-----------------------------------------------------------------\n";
		cout << "Command :         View TimeLine\n";
		cout << "-----------------------------------------------------------------\n";
		currentUser->View();
	}

}

/////////////////////////////////////////////////////////// 
int main()
{
	MyApp MyApp;
	MyApp.Load();
	MyApp.Operate();
	return 0;
}
