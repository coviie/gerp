A. Written by : Jia Wen Goh
	         On : 21-04-2017

B. ** Purpose of program **
   The program will index all files stored in the given directory (and its 
   sub-directories) by storing all words (and related information, i.e.
   the file, line number and contents of the line that the word was stored in).
   The user should then be able to query this index with either a 
   case-sensitive or case-insensitive search (query should be near-instant).
   Results should then be printed as:
	     filename/With/Path:Line#: LineContents

C. ** Uploads **
   -= gerp =-
   gerp.cpp	End-user interface/main; Indexes the directory given from 
		the cmd line, then takes input from cin and either searches 
		(either case sensitive or insensitive) or quits. 
		Also handles 'special' user input (i.e. entering "@i" 
		with no inputs and quitting).
   
   -= Trie =-
   Trie.h	Trie Class Header & Definition; 
		Trie will store the every word parsed from the file. The 
		terminating character of each word is a Key struct (defined 
		below).
   Trie.cpp	Trie Class Implementation;
   Key.h	Key struct definition; Struct will contain:
		- file (i.e. the n-th file stored in the file list)
		- line (i.e. what line the word was found in)
		- data (i.e. the contents of the line the word was found in)
   
   -= TreeTraversal =-
   TreeTraversal.h		TreeTraversal Class Header & Definition;
				TreeTraversal traverses the directory, storing
				filenames into a vector string.
   TreeTraversal.cpp		TreeTraversal Class Implementation;
   testTreeTraversal.cpp	TreeTraversal test file - prints all the files
				that the directory (and its subdirectories) 
				hold
   
   -= stringProcessing =-
   stringProcessing.h	stringProcessing Definition;
			stringProcessing strips all bounding non-alphanumeric 
			characters from the given string.
   stringProcessing.cpp	stringProcessing Implementation
   
   -= Indexer =-
   Indexer.h		Indexer Class Header & Definition
   Indexer.cpp		Indexer Class Implementation
   testIndexer.cpp	Indexer test file
   
   -= Etc =-
  - Makefile		    Automates the compilation and linking commands
			    that users would have to otherwise type by hand.
  - README		    Readme

D. ** How to compile and run **
   gerp:	[compile]: make
		[run]: ./gerp DirectoryToIndex

E. ** Architectural overview **
   
    [directoryName] from command line
     |
   .=|= TreeTraversal ===.
   " (taken in by)       "
   "  |			             "
   "[directoryList]      "
   "  | ^       ^        "
   "  | | 	    |	       "
   "  | |       --------------------[FSTree.h] (tree that contains all files)|
   "  | ----------------------------[DirNode.h] (building block of FStree)
   ' =|================= "
      |
      (used by Indexer as a reference on what files to look into, and their
      | locations)
      |
   .==| Indexer ===.		        [          Trie         ]
   "  |	           "				      ^               ^
   "  v	           "				      |               | 
   "[fileList]	   "			        |               | 
   " - Files are then read, and 	|               |
   "   words are processed and		|               | 
   "   stored into: --------------+               |
   '==============='			                     (searches into the Trie;
   					  |                                 returns a Key that is 
          [query] from cin ----------------------  used in printing)
          [printing]

   
F. ** Design **
   Data Structure: TRIE
   Tries are a vertical, n-ary tree data structure, where each Node has data 
   (in this case, a char) and an array of pointers (the Node's 'children').
   Each Node's array of pointers is length-94 (i.e. can contain 94 possible
   ASCII characters).   
   Each terminating character of a word will contain some information 
   that can be used to determine if it's the terminating character.
     
   For both adding and querying:
	Adding: O(n), where n is the length of the word
	Query:  O(n), where n is the length of the word
   This occurs because the search/add 'traverses' down the word, looking
   or adding each character in a specific cell of the array (this lookup
   or adding is O(1) as the specific cell is related to the ASCII value
   of the character).
   
   I used this data structure as:
   	- Space-efficient, as the node-structure means that 'parents' are 
   	  shared, i.e. "to" and "the" shares the same "t" parent node. Thus,
   	  this allows me to store different variations of words without much
   	  extra space needed (e.g. "the" "tHe" "thE")
	- Time-efficient; Querying is just length O(n), and so this makes for 
	  time-efficient lookup
   Moreover, the terminating character can store the important information
   about the word location (file, line number and line contents), making
   it ideal for this application (printing just requires accessing this key).
   
   
   Design & Notable Algorithms:
   Overall structure: TreeTraversal -> Indexer -> Gerp
   
   0. -- Cmd Line --
      Take in the directory to index from the command line
      
   1. -- TreeTraversal --
      The program starts by traversing the directories specified, storing
      the filenames into a vector<string>. Filenames are stored with their
      'root' directories (i.e for file README, it is stored as:
		/h/jgoh01/comp15/proj2/README 
      rather than just README). 
      
      * crawl
      The steps for processing are deliberate, i.e.
	1. Process files (store them into the vector<string>)
	2. Enter subdirectories
      This tail-end recursion created the stack-frame only at the end
      of the function for the recursion call; this is more memory-efficient
      since you don't have pending files to read before the recursion steps.
   
   2. -- Processing files --
      Indexer then refers to this vector<string> and opens all files. The 
      processing of each file is as such:
	- ifstream.open(filename)
	- gets each lines contents (noting the file number, line number of
	  the contents, and the actual contents itself)
	  > then parses* each line
 
   - 2.1 -- Parsing words --
         Indexer sends this line of contents into stringstream. Each word
         in the line is then extracted, processed, before being stored in
         the Trie.
      
         e.g.
		1: hello world !@#!%lorem!@#!%
	    Step1: hello
		   ^ (no) non-alphanumeric chars stripped and added
	    Step2:	 world
			 ^ (no) non-alphanumeric chars stripped and added
	    Step3:	       lorem
			       ^ non-alphanumeric chars stripped and added
		
	 * There is an additional condition "if (word != "")" before the word
	   is added to the Trie. This helps optimize the adding of words, as
	   during testing, I noticed a lot of blank strings were being added.
	   Since blank strings are useless in queries (and only clogs up
	   runtime, I made the function skip these strings)
   
   - 2.2 -- Adding words to Trie --
	The stripped words (and its location data stored in the Key) get sent 
	into the Trie. The terminating character of the word is this Key 
	(good and efficient place to store info; when searched, function just
	 has to look at this terminating character to extract the important
	 info)
	
	i.e.
			   [root]
			/  /   \   \
		     [h]  [w]  [l] [91 other blank arrays]
		      |    |    |
		     ...  ...  ... 
		      |    |    |
		     [o]  [d]  [m] 
		      |    |    |
		Key:[1:1][1:1][1:1]
	
	* 94-size *children & convertASCII
        When looking at the ASCII table, I realized that the first 33 
    	characters aren't used/displayed. Thus, to be more memory-efficient 
    	(especially important in very large input files), I made a 94-size
    	array at each 'level' of the Trie (rather than 128), and offset every
    	input by 33. This prevents wasted-space in the array, maximizing space
    	efficiency. 
    	Moreover, to ensure O(r) lookup, where r is the length of the query, 
    	We can't go any lower, else we need to expand the array/use a hash-
    	like structure, which doesn't ensure constant lookup at each 'level'.
	
	   (additionally, the use of a Trie allows us to extend the application
        of the gerp to search for binary (extended ASCII) characters; we just
        need to change the array size from 94 -> 94+128).
	
	* keyExists
        Initially, when storing the Key in the terminating character, I 
        iterated through the vector<Key> to check for duplicates. However, 
        this method was not optimal, as everytime a Key is added, the runtime
        of this algorithm is O(n), where n = number of Keys already inside. 
        This noticeably slowed down the programme.
        However, since duplicated Keys only exist for words on the same line,
        the algorithm should only check with the last Key added.
        i.e.:
         
            Key   4:1				
                  v
    	   1: hello			Step1: 4:2 checks against 4:1
    	   2: hello world hello 	Step2: 4:2 checks against 4:2;
    	      ^	          ^		       2nd 4:2 isn't added
            Key:  4:2	  4:2
    	
        In the above example, a duplicated word in line 1 will have a different
        key than the words in line 2. Thus, we only need to check against
        the most recent one (such that if 1 or more duplicates exist, their 
        Keys won't be added). This reduces the runtime to O(1), optimizing the
        word storage quite effectively.
        
        * Storing the lineContents inside the Key 
        When initially planning the design, I used a hashTable to store the 
        line contents. When retrieving the search results, the Key (which then
        only contained file number and line number) would be used to 'point'
        to the correct cell that contained the line number. This increased
        space-efficiency, as the lineContents will only be stored once (vs.
        current implementation where it is stored multiple times, once for
        each word in the line).
        
        However, this hashing process noticeably slowed the programme down
        (especially with expansion, where every element in the table had to
         be copied over every expansion. This posed a problem when the hash
         table size was extremely large; the program 'halted' everytime 
         expansion was needed). 
         
        Thus, considering time-efficiency vs. memory-efficiency, I decided
        to store the lineContents in the terminating character (additionally,
        with larger inputs, this trade-off becomes far more effective, since
        the transferring of this large amounts inputs during expansion takes
        an unfortunate amount of time). Moreover, even if I were to brute-
        force the hashTable size (to ensure little expansion), this would be
        memory-inefficient for small inputs as large amounts of hashTable 
        cells would be unfilled, negating the advantage it has.
  
   2. (con't)
      The above process 2.1 and 2.2 are repeated till the all files are 
      processed.

   3. -- Search --
      Once the files are indexed, gerp (main) then prompts the user for input
      into cin. Depending on the input, the following outcomes will happen:
        	AnyString		Case-sensitive search on the string
        	@i or @insensitive	Case-insensitive search
        				> How it should work:
        				  - @i AnyString -> searchInsensitive
        				  - @i		 -> waits on next input
        				if: hello	 -> searches on "hello"
        				or: eof		 -> does searchInsensitive on 
        						    "i"  
        	@q or @quit		Quits the program
	
      When a query is entered, gerp sends this query into the indexer, which
      will be passed into the Trie, and the related search on it will be done. 
      This search by Trie will return a vector<Key>, which will be processed
      by Indexer; relevant output will then be printed onto cout, in the 
      format:
	       /filepath/filename:n: fileContents	, where n is the line number
    
    - 3.1. -- Searching into Trie --
      * searchSensitive
        In a similar-process to the addWord algorithm, the case-sensitive 
        search will traverse down the 'levels' in the Trie to search for the
        word. In detecting whether the word was found, the function would 
      	return a vector<Key>; if no such words existed in the indexed files, 
      	this vector would be empty, and will be interpreted by gerp (and 
      	nothing will be printed). However, if not, this vector will 
      	contain all the important information that will be extracted by 
      	gerp to print.
	
      * searchInsensitive
        The search recursively searches the Trie by considering both upper
        and lower cases of each letter at each 'stage' of the word (if they
        are letters, else it just considers the nonalpha char). This is done
        so all combinations are searched/accounted for.
        
   3. (con't)
      The results are then printed on to cout, and input is taken from the 
      user again (unless eof or @q).      

