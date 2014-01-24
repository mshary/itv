# ITV Encryption Algorithm

A fast, simple yet effective on-wire encryption algorithm for data (preferably plain text) communication over LAN / WAN.

### History

This algorithm has its roots in Caesar Cipher. The original Cipher suggests that each letter in plaintext is replaced by some fixed number of positions down the alphabet. For example with left shift of 3, 'D' would be replaced by A, 'E' would become 'B' and so on.

The Caesar Cipher was first cracked by an arab scientist Al-Kindi in 9th century through discovery of frequency analysis (some letters are used more often in a language then others, the anaylsis can easily determine shift value and direction). He proposed a modification to algorithm to have different shift value for each letter with same shift direction (left or right).

However with advancement in frequency analysis during WWI and WWII, the modified version of Caesar Cipher was broken down. This document explains a further improvement to the cipher using basic computer science concepts.

### What is it?

ITV stands for ID, Tag and Value. It has two variants character based ITV and word based ITV. Let us understand character based ITV (since it is much similar to Caesar Cipher).


## Character Based ITV

When using character sets in computer, each letter is basically assigned an integer value which is actually used and understood by computers for internal use. For example using ASCII character set, letter 'A' is represented by integer 65, 'B' is 66 and so. 

In ITV algorithm we define integer 65 as "ID" and letter A as its "Value". Thus entire ASCII character set is just a table of IDs and their Values. We add another column to this table, namely the "Tag".

Tag should be "randomly" generated value within ID range. For example, considering all capital letters in ASCII, we have first ID as 65 (for value A) and last is 90 (for letter Z). So any random value within range 65 - 90 can be used as a Tag.


### ITV Table

Thus we have ITV table, having ID, Tag and Value for each letter in character set. We initialize the ITV table by using Tag same as ID. So, an ITV table over capital letter would be,


ID    TAG    Value
--    ---    -----
65    65     A
66    66     B
67    67     C
68    68     D
69    69     E
70    70     F
..    ..     .

89    89     Y
90    90     Z


### How Encryption Works?

Using above ITV Table, suppose we want to encrypt the word "ABBA". The encryption is done as follows,

1. Determine ITV table row for first letter of the word as Value, in this case, first letter is 'A'. Let call it ITV record X.

2. Generate a random integer say 67, within range 65 - 90. Determine ITV table row which has ID = 67. Let call it ITV record Y.

3. In ITV record Y, save current ID as TAG and ID of ITV record X as new ID. ITV table becomes,

ID    TAG    Value
--    ---    -----
65    65     A
66    66     B
65    67     C
68    68     D
69    69     E
70    70     F
..    ..     .

89    89     Y
90    90     Z

4. In ITV record X, save current ID as TAG and use generated integer 67 as new ID, ITV table becomes, (note that no duplicate values in columns ID and TAG, the integeral values are merely switches with one another).

ID    TAG    Value
--    ---    -----
67    65     A
66    66     B
65    67     C
68    68     D
69    69     E
70    70     F
..    ..     .

89    89     Y
90    90     Z

5. Thus we have encrypted version of letter 'A' as letter 'C' (current ID of value 'A').

6. Similarly we encrypt next letter 'B' to get letter 'Y'.

7. The third letter is again 'B'. Although previously we determined encrypted value for 'B' as 'Y' but we repeat the above process to get a different letter say 'Z'. It is important to repeat the above process for every single character in the word, no matter how many times it is repeated in the word. This will ensure frequency analysis to fail since each letter will have 26^26 substitution possibilities.

8. When all characters are processed in a word, we get encrypted version of the word by using ID and TAG value for each encrypted version of each character, e.g.

	Value (unencrypted) => ID TAG (encrypted)

Thus, we may have,

	ABBA => 65 67 66 89 89 90 65 70 

OR Simply,

	ABBA => ACBYYZAF 
(by using converting integers to letters according to standard ASCII characterset)

### Security Note

1. You should properly initialize ITV table before production use, otherwise at least a first few letters of the word will be exposed. A properly initialized ITV table is the one which has no ID exact same as TAG or Value. To achieve this, encrypt a word / sentence which has all letters of ITV table Values, e.g. for ITV table mentioned above, one can encrypt below sentense and discard its output.

A QUICK BROWN FOX JUMPS OVER THE LAZY DOG.

2. Length of encrypted word would be exactly double the length of actual word. You should randomly add a random letter (within same range) at the end of words in each sentence, so that some words has even and others have odd length.

3. Space between words and unrecognized letters / symbols / punctuation marks etc. (which are not present in ITV table) should remain as-is in the encrypted sentence.

4. For duplex communication, it is recommended that each sender has its own ITV Table. Using single table for on both sides may cause synchronization issues.


### How Decryption Works?

For decryption, one MUST have same version of ITV table, that was used to encrypt the original text.

1. Take first pair of characters in the encrypted word. Convert both to integers (according to standard ASCII character set).

2. Find ITV record matching first integer as ID in ITV table. Save ID to TAG and use second integer as new ID. The VALUE of this record is unencrypted character.

3. Find ITV table record matching second integer as ID, Save ID to TAG and use first integer as new ID.

4. Run through pairs of character in the word to determine unencrypted characters. Letters / symbols / punctuation marks etc. that are not matched in ITV table should be present in encrypted word.

5. Any unpaired character at the end of word should be discarded.

### Misc. Notes

1. After decryption completes states of ITV table each side (the send who sent the encrypted text and receiver how decrypted the text) would be identical.

2. In practice TAG is drived from ID and both ID and TAG have no direct relation with VALUE in ITV table neither for encryption nor for decryption. So we can use ANY distinct set of integers as ID (they don't even need to be consecutive). For TAG we will generate an integer within range of 0 to number of records in the table, say N and use ID of that Nth record as TAG. This way it is even possible e.g. to encrypt message in German that looks like Russian in encrypted form OR message in Chinesse decrypts to Korean etc. etc.

3. To further enhance security it is possible to break encrypted message into two, i.e. first consists of all IDs (first integers of each character pair) and second consists of all TAGs (second integers of each character pair). Each part is transmitted using different medium or communication channel. However recipient would need both parts merged together before it can attempt to decrypt it.


## Word Based ITV

It works almost exactly same as Character Based ITV. The only difference is that in character based ITV, we have well-defined character sets which both us and computers understand.

If we have complete list of words of any language then we can define our own ITV table consisting of words as VALUE. For ID and TAG we can use any integer range.

The encryption and decryption will work the same way as for character based ITV algorithm. However encrypted sentence will be merely a space separated list of integers which can be transmitted in binary format. The recipient will take pairs of integers and decrypt them accordingly.


### Misc. Notes

1. A human language consists of hundreds of thousands of words however an average human being merely uses 2,000 - 3,000 words of it in daily life. So ITV table can be shorten down significantly. However if plain text consists of any words that are not present in ITV table, they will be skiped in encrypted form and will be missing in after decryption.

2. Like character based ITV, ID can be any integer range and does not need to be consecutive.

3. Transmitting encrypted data as integer is recommended rather then string i.e. '65536'=> 5 bytes, comparing to integer 65536, which only takes 2 bytes. This may save some bandwidth. 

4. Though preserving bandwidth is not the aim of this algorithm but one can zip the encrypted string to compensate for bandwidth.


## Using The Sample Code

Sample code is provide as proof of concept in C++ using STL library. 

To compile the code using GNU C++ compiler,

	g++ -o itv -Os *.cpp

OR simply,

	make clean
	make all

To run the code,
	
	./itv

To utilize the code in your own projects, import following files in your project,

	itv.h / itv.cpp => defines an ITV record
	itv_table.h / itv_table.cpp => defines an ITV Table.
	itv_utils.h => defines some utility functions (optional).

For reference implementation of Character Based ITV algorithm, include or read through,

	itv_ascii.h / itv_ascii.cpp


For reference implementation of Word Based ITV algorithm, include or read through,

	itv_word.h / itv_word.cpp


Feel free to add and/or extend given C++ classes (per MPL v2.0 license).

## About Author

The concept and sample code was developed by Muhammad Shahzad Shafi (shahzad at voip-demos dot com). The sample code is released under MPL v2.0 license.

The concept and sample code are intended for scientific research and peaceful means.

