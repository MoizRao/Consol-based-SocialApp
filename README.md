# Social Network Application
A C++ based social networking application implementing Object-Oriented Programming principles to simulate core social media functionalities.

## 📋 Overview
This application simulates a social media platform with features similar to Facebook, allowing users to:
- Create and manage profiles (both user profiles and pages)
- Post content and interact with posts
- Manage friend connections
- Like and follow pages
- Share memories
- View timelines and news feeds

## 🏗️ Architecture
The application follows OOP principles with the following key classes:

### Core Classes
- `MyApp`: Main controller class managing the application
- `Profile`: Abstract base class for both Users and Pages
- `User`: Represents a user profile
- `Page`: Represents a business/fan page
- `Post`: Handles post creation and management
- `Comment`: Manages comment functionality
- `Memory`: Special type of post for sharing memories
- `Date`: Handles date-related operations
- `Activity`: Manages user activities and status updates
- `Helper`: Utility class for string operations

### Class Hierarchy
```
Profile (Abstract)
├── User
└── Page

Post
└── Memory
```

## 📁 Input Files
The application reads data from four text files:

### 1. SocialNetworkUsers.txt
- Contains user information
- Format:
  - Total number of users
  - For each user:
    - User ID
    - First name
    - Last name
    - Friend IDs
    - Liked page IDs

### 2. SocialNetworkPages.txt
- Contains page information
- Format:
  - Total number of pages
  - For each page:
    - Page ID
    - Page title

### 3. SocialNetworkPosts.txt
- Contains post information
- Format:
  - Total number of posts
  - For each post:
    - Post type
    - Post ID
    - Posting date
    - Post content
    - Activity (if applicable)
    - Posted by (User/Page ID)
    - Liked by (User/Page IDs)

### 4. SocialNetworkComments.txt
- Contains comment information
- Format:
  - Total number of comments
  - For each comment:
    - Comment ID
    - Post ID
    - Commenter ID
    - Comment text

## 🔑 Key Features

### User Management
- Create and manage user profiles
- Add/view friends
- Like and follow pages
- View personalized timeline

### Content Management
- Create posts with text and activities
- Comment on posts
- Like posts
- Share memories
- View post history

### Timeline & News Feed
- View personal timeline
- View home feed with friends' and pages' posts
- Filter recent posts
- View and share memories

## 💻 Implementation Details

### Memory Management
- Implements proper memory allocation and deallocation
- Uses dynamic arrays for storing posts, comments, friends, and liked pages
- Handles deep copying of strings and objects

### Data Structures
- Uses pointer arrays for managing relationships
- Implements linked structures for timeline management
- Maintains separate lists for friends and liked pages

### Helper Functions
- String manipulation utilities
- Date comparison and management
- Search functionality for users, pages, and posts

## 🚀 Usage
1. Prepare the input text files with required data
2. Compile the application using a C++ compiler
3. Run the executable
4. The application will automatically load data and execute predefined operations

## 🔍 Search Functionality
- Search users by ID
- Search pages by ID
- Search posts by ID
- Combined search for both users and pages

## ⚠️ Limitations
- Fixed maximum limits for:
  - Friends per user (10)
  - Liked pages per user (10)
  - Comments per post (10)
- Static data input through text files
- Predefined operation sequence

## 🛠️ Future Enhancements
- Dynamic limits for friends and pages
- Interactive user interface
- Database integration
- Real-time updates
- Media content support
- Enhanced privacy settings
