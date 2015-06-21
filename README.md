# ITV Encryption Algorithm
A fast, simple yet effective encryption algorithm for data communication over computer networks.

### History
This algorithm has its roots in *Caesar Cipher*. The original cipher suggests that each letter in plain text is replaced by some fixed number of positions down the alphabet. For example, with left shift of 3, 'D' would be replaced by 'A', 'E' would become 'B' and so on.

The *Caesar Cipher* was first cracked by an Arab scientist Al-Kindi in 9th century through discovery of frequency analysis (some letters are used more frequently in a language then others, the analysis can easily determine shift value and direction). In 15th century, the *Polyalphabetic Cipher* was introduce, which suggested to use a secret word, each letter in the word was used as shift for plaintext letters (like *Caesar Cipher*). However in late 19th century, this too was broken down. 

On Sept. 1, 1945, Claude Shannon proved mathematically a further enhancement to the cipher, which proposes random shift to each letter of plaintext, as the perfect solution for the encryption. It is now known as *One-Time Pad Encryption*. The ITV algorithm is intends to extend and apply this *One-Time Pad Encryption* using some basic Computer Science concepts.

### What is it?
ITV stands for **ID**, **Tag** and **Value**. It has two variants character based ITV and word based ITV. Let us understand character based ITV (since it is easier to understand for anyone already familiar with *One-Time Pad Encryption*).

## Character Based ITV
When using character sets in computer, each letter is basically assigned an integer value, which is actually used and understood by computers for internal use. For example, using ASCII character set, letter 'A' is represented by integer 65, 'B' is 66 and so on.

In ITV algorithm, we define a table with three columns. The first column represents the numeric value of characters, this column is known as the **ID** of each character. The second column also holds numeric value randomly generated within range of **ID** column, this column is known as the **Tag**. The third column contains the actual character, which we call the **Value** column.

### ITV Table
So considering, numeric values *65, 66, 67 ... 90* as **ID** and letter *A, B, C ... Z* as respective **Value**, we can define **ITV Table** over ASCII character set. As for **Tag** column, it should be random but non-repeated number within range *65 - 90* but for simplicity lets assume it is same as **ID** column for now.

Thus we have ITV Table with ID, Tag and Value for each letter in English character set. This would look something like this,

````
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
````

### How Encryption Works?
Using above ITV Table, suppose we want to encrypt the word "ABBA". The encryption is done as follows,

- Take the first letter, in this case 'A', and find the corresponding row in ITV Table which has this letter in *Value* column. Lets call it ITV Table record X.
- Generate a random number; say 67, within range 65 - 90. 
- Determine ITV table row which has *ID* = 67. Let call it ITV record Y.
- In ITV Table record Y, save current ID as TAG and ID of ITV record X as new ID. ITV table becomes,

````
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
````

- Now in ITV Table record X, save current ID as TAG and use generated number 67 as new *ID*. ITV Table becomes,

````
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
````
*(Notice that no duplicate values in columns ID and TAG, the numerical values are merely switched with one another)*

- Thus, we have encrypted version of letter 'A' as letter 'C' (i.e. current ID of value 'A').
- Similarly we encrypt next letter 'B' to get letter 'Y' by following same process as above.
- The third letter is again 'B'. Although previously we determined encrypted value for 'B' as 'Y' but we **MUST** repeat the above process and get a different letter say 'Z'.

*(It is important to repeat the above process for every single character in the plaintext, no matter how many times it is repeated in the word. This will ensure frequency analysis to fail since each letter will have *26^26* substitution possibilities)*

- When all characters are processed in a word, we get encrypted version of the word by using ID and TAG value for each encrypted version of each character, e.g.

	*Value (unencrypted) => ID TAG (encrypted)*

Thus, we may have,

````
	ABBA => 65 67 66 89 89 90 65 70 
````

OR Simply,
````
	ABBA => ACBYYZAF
````
*(by converting integers to letters according to standard ASCII character set)*

- If there exist any character that is not present in ITV Table, then it will not be encrypted and thus transmitted as is. Therefore, it is important that ITV Table has all the characters and symbols that expected to be used in plaintext, i.e. even "space" and "full-stop" characters are important, if they are not included in ITV table then one can identify end of word and end of sentence marks in encrypted text.

For improved security it is highly recommended to randomly shuffle ID column values in ITV Table before sharing it with the receiver. The simplest way to do that is to encrypt a plaintext that contains all characters present in ITV Table and discard the output.

Additionally the generated encrypted text can be broken into two pieces, one consisting only of **ID** values (odd characters in encrypted text) and other consisting only of **Tag** values (even characters in encrypted text) and sent over two different transactions (or even two different communication mediums).

Also note that since **ID** has no direct relationship with **Value** column, so **ANY** numeric range can be used in it. Thus, we can e.g. use Hebrew character set range (UTF8 0x500 - 0x5FF) to represent **ID** data that corresponds to **Value** in Arabic character set (UTF8 0x600 - 0x6FF), in which case the plain text would be in Arabic but encrypted text would appear as Hebrew. (see example usage below).

### How Decryption Works?
For decryption, the receiver **MUST** have exact same ITV Table, that was used to encrypt the original text. Thus, we can say the ITV Table is the **Key** in cryptographic term that is required to decrypt the data. However, the beauty of this algorithm is that the ITV Table constantly changes as it encrypts more data on sender side, while the receiver side keeps its ITV Table synchronised as it decrypts the received that. The receiver will have exact same ITV Table after decryption as the ITV Table on sender side after encryption. Therefore, for next communicate session the sender does not need to send the ITV Table again to the receiver.

This however, has two consequences,

1. The communication is half-duplex, i.e. sender can only send data and receiver can only receive data. It receiver wants to send data as well, then it should create a separate ITV Table and use it for encryption same way as sender side is doing. Thus in such case, each side will have two ITV Tables, one that is used to encrypt data that it wants to send and the other to decrypt that it receives from the other side.

2. Communication **Must** be synchronous, that is the receiver must decrypt the data received in first transaction to be able to decrypt data in second transaction and so on. If any data is lost in transmission then decryption will fail (i.e. produce garbage text). This mechanism ensures communication integrity.

Here is how to the decryption works,

- Take first pair of characters in the encrypted word. Convert both to integers (according to standard character set).

- Find ITV Table record matching first integer as **ID**. Save ID to TAG and use second integer as new ID. The VALUE of this record is the unencrypted character. If there is no matching record then convert it back to character and use it as is (this character is not encrypted and thus no need to be decrypted).

- Find ITV Table record matching second integer as **ID**. Save ID to Tag column and use the first integer as new ID.

- Run through all pairs of character in the word to determine unencrypted characters and so on.

## Word Based ITV
It works almost exactly same as Character Based ITV. The only difference is that in character based ITV, we have well-defined character sets which both us and computers understand.

If we have a dictionary of words that both sender and receiver agree upon and do all the communication according to it then we can use each word in the dictionary as value for **Value** column and assign each word its own unique numeric value in **ID** column then we can construct *Word Based ITV Table*, which would encrypt plaintext word-wise and produce numeric encrypted text following same encryption / decryption rules as *Character Based ITV Table*.

## Using The Sample Code
Sample code provided as proof of concept in C++ using STL library. You must have fairly recent compiler to build it since it heavily used C++ 11 specification.

To compile the code using GNU C++ compiler (v4.7 or better),

````
	make clean
	make all
````

This will produce itv.so library, which can be installed along with all headers files by,

````
	make install
````

Sample output of Character Base ITV,

````
Original: a quick brown fox jumps over the lazy dog.
Encrypted: sf6Tl0/=lFS!$&T4m"^;:na`W+4 ZGnM(V jNs=_w2|,zajMjvLO=@;XMbcc}Q@WbAd]f!#y.uA84PvYU&#8
Decrypted: a quick brown fox jumps over the lazy dog.
````

Since v3.0, *Word Based ITV* implementation is no longer provided in sample code.

To utilize the code in your own projects, import following files in your project,

````
	itv.h / itv.cpp => defines an ITV record
	itv_table.h / itv_table.cpp => defines an ITV Table.
	itv_utils.h => defines some utility functions (optional).
````

For reference implementation of Character Based ITV algorithm, include or read through,

````
	itv_characters.h / itv_characters.cpp
````

## Example Usage

````c++
#include <iostream>
#include <string>

#include "itv_utils.h"
#include "itv_characters.h"

using namespace std;

int main() {
	/* create ITV Table,
     * One can use any text encoding. Here we use UTF8.
	 * IDs use Hebrew, thus encrypted text will be in Hebrew
	 * Values use Arabic, thus plain text will be in Arabic
	 */
	ITV_Characters sender = ITV_Characters(0x500, 0x600, 0x6FF - 0x600);
    sender.load(0x20, 0x20, 1);	/* Add space character */
    
    /* randomly shuffle IDs */
    sender.shuffle();
    
    /* ITV Table that receiver needs to decrypt data */
    std::string itv_table = sender.dump();
    
	/* sample text to encrypt, we are using UTF8 encoding here */
	std::string str = u8"أزمة اليمن: الحوثيون يتقدمون في عدن رغم الغارات الجوية";
    std::list<size_t>* msg = from_utf8(str);
    
    cout << "Original: " << str << endl;
    
    /* encrypt the text */
    std::list<size_t> *encrypted_text = sender.encode(*msg);
    
    /* convert encrypted text to UTF8 and send it, here we just print it */
    cout << "Encrypted: " << to_utf8(*encrypted_text) << endl;
    
    
    /* On Receiver side, 
	 * the ITV Table is initialised with table dump from sender side
	 */
    ITV_Characters receiver = ITV_Characters(itv_table);
	std::list<size_t> *decrypted_text = receiver.decode(*encrypted_text);
    std::string plain = to_utf8(*decrypted_text);
    
    if (str == plain) {
    	cout << "Decrypted: " << plain << endl;
    } else {
    	cout << "Failure: " << plain << endl;
    };

	return 0;
};

````

To compile the program,

````
g++ -Wall -std=c++11 -L./ -litv -o itv main.cpp
````

Feel free to add and/or extend given C++ classes (per MPL v2.0 license).

## About Author
The concept and sample code was developed by Muhammad Shahzad Shafi (shahzad at voip-demos dot com). The sample code is released under MPL v2.0 license.

The concept and sample code are intended for scientific research and peaceful means.
