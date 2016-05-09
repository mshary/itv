# ITV Encryption Algorithm
A fast, simple yet effective encryption algorithm for data communication over computer networks.

### History
This algorithm has its roots in *Caesar Cipher*. The original cipher suggests that each letter in plain text is replaced by some fixed number of positions down the alphabet. For example, with left shift of 3, 'D' would be replaced by 'A', 'E' would become 'B' and so on.

The *Caesar Cipher* was first cracked by an Arab scientist Al-Kindi in 9th century through discovery of frequency analysis (some letters are used more frequently in a language then others, the analysis can easily determine shift value and direction). In 15th century, the *Polyalphabetic Cipher* was introduce, which suggested to use a secret word, each letter in the word was used as shift for plaintext letters (like *Caesar Cipher*). However in late 19th century, this too was broken down.

On Sept. 1, 1945, Claude Shannon proved mathematically a further enhancement to the cipher, which proposes random shift to each letter of plaintext, as the perfect solution for the encryption. It is now known as *One-Time Pad Encryption*. The ITV algorithm is intends to extend this *One-Time Pad Encryption* using some basic Computer Science concepts.

### What is it?
ITV stands for **ID**, **Tag** and **Value**. It was originally designed for secure network comminication over public Internet however it can also be used for permanent data storage on disk. It has two variants, character based ITV and word based ITV. Let us understand character based ITV.

## Character Based ITV
When using character sets in computer, each letter is basically assigned an integer value, which is actually used and understood by computers for internal use. For example, using ASCII character set, letter 'A' is represented by integer 65, 'B' is 66 and so on.

In ITV algorithm, we define a table with three columns. The first column represents the numeric value of characters, this column is known as the **ID** of each character. The second column also holds numeric value randomly generated within range of **ID** column, this column is known as the **Tag**. The third column contains the actual character, which we call the **Value** column. This table is called *ITV Table* and acts as *encryption key* for this algorithm.

### ITV Table
So considering, numeric values *65, 66, 67 ... 90* as **ID** and letter *A, B, C ... Z* as respective **Value**, we can define **ITV Table** over ASCII character set. As for **Tag** column, it should be random but non-repeated number within range *65 - 90* but for simplicity lets assume it is same as **ID** column for now.

Thus we have ITV Table with ID, Tag and Value for each letter in English aphabets. This would look something like this,

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
For decryption, the receiver **MUST** have exact same ITV Table, that was used to encrypt the original text. Thus, we can say the ITV Table is the **Key** in cryptographic term that is required to decrypt the data. However, the beauty of this algorithm is that the ITV Table constantly changes as it encrypts more data on sender side, while the receiver side keeps its ITV Table synchronised as it decrypts the received data. The receiver will have exact same ITV Table after decryption as the ITV Table on sender side after encryption. Therefore, for next communication session the sender does not need to send the ITV Table again to the receiver.

This however, has some consequences,

1. The communication is half-duplex, i.e. sender can only send data and receiver can only receive data. It receiver wants to send data as well, then it should create a separate ITV Table and use it for encryption same way as sender side is doing. Thus in such case, each side will have two ITV Tables, one that is used to encrypt data that it wants to send and the other to decrypt that it receives from the other side.

2. Communication **Must** be synchronous, that is the receiver must decrypt the data received in first transaction to be able to decrypt data in second transaction and so on. If any data is lost in transmission then decryption will fail (i.e. produce garbage text). This mechanism ensures communication integrity.

3. The checksum of ITV Table can be send with encrypted data by sender which receiver may check against its own ITV Table checksum to verify its integrity **before** doing actual decryption. This helps identifing data loss e.g. over network and allow key re-negotitation or to terminate the session.

Anyways, here is how to the decryption works,

- Take first pair of characters in the encrypted word. Convert both to integers (according to standard character set).

- Find ITV Table record matching first integer as **ID**. Save ID to TAG and use second integer as new ID. The VALUE of this record is the unencrypted character. If there is no matching record then convert it back to character and use it as is (this character is not encrypted and thus no need to be decrypted).

- Find ITV Table record matching second integer as **ID**. Save ID to Tag column and use the first integer as new ID.

- Run through all pairs of character in the word to determine unencrypted characters and so on.

## Word Based ITV
All existing encryption algorithms today have one common flaw, that is, they all have clear encryption / decryption semantics. This means any human or AI capable machine could easily identify if any text is encrypted or not. If this person or thing has the capability to interrogate the data sender or receiver, it may force them to reveal the original message or at minimum, block their communication channel so that no further encrypted transmission is possible between them.

This poses a great threat to encryption users. Many countries in the world, even the so called champions of freedom of expression and civil liberties are indulge in crimes of mass surveillance of not only the foreigners but also their own citizens. These ordinary Internet users on the other hand, have no way to protect their privacy without being spotted and possibly being condemned by the authorities in their country.

The aim of word based ITV encryption algorithm is to encrypt data metaphorically. That is, neither the computer nor a human should be able to identify if any given data is encrypted or not. It should appear as ordinary plain-text with casual meaning, only a computer program designed specifically to decrypt the data should be able to identify and process it.

The base implementation idea is similar to Character Based ITV. The main difference is the use of language dictionary instead of character set and instead of mapping them to integers, map them to words from another language (or the same language for simpler implementations). For example, an encrypted text may look like,

```
Then I said I love you.
```

This may decrypt to,

```
Du Scheiße Kopf!
```

As you can see both encrypted and decrypted texts have completely different meaning, though they both look plain-text to their speaks.

The main challenge here is to make encrypted text somewhat meaningful, so it makes some sense as a sentence. This requires the implementation program to have some knowledge of both languages and their basic grammar.

**Edit:**
*In this age of social media, people no longer care for correct spelling and grammar in their writings, which significantly simplifies the implementation of this algorithm, all we need is a big pool of slang words in respective languages and the knowledge of their grammatical classification e.g. whether it is a noun, verb or adjective etc. etc.*

This is a work in progress and currently no sample code is available in this public repository.

## Algorithm Features
1.	A new type of encryption algorithm which is stronger than both traditional algorithm types, i.e. block encryption algorithms and stream encryption algorithms. The encryption strength is input plaintext length multiplied by key length raise to power of key length, i.e. N x K ^ K (where N = length of input plaintext and K = key length).


2.	Once initialized the encryption key dynamically changes as more and more data is encrypted. The key at decryption party end remains synced as it decrypts data received from encryption party end.

3.	This dynamically changing key behaviour is depended on following three aspects, which ensure different non-deterministic encryption output even if any two of below three dependencies have been compromised.
	- A Random Number Generation (RNG) source.
	- Input data for encryption.
	- Current key fingerprint.

4.	Support for checksum, 
	- The encryption party may generate key checksum before encryption and send it with encryption output, which destination may check against its key’s checksum to determine if it would be able to decrypt the received data or not.

	- The decryption party may also generate key checksum after doing decryption and send it, which encryption party may check against its key’s checksum to determine if destination’s key is in sync and would be able to decrypt data any further.

	- This checksum is numeric value unique to the key and is not generated using any existing hashing algorithms.

5.	Encryption key length can be of,
	- Any arbitrary length, which can be defined at initialization time and then remains fixed for rest of the session.
	- Encryption and decryption parties may save the key or re-negotiate it for next sessions.
	- As the encryption strength increases with key length so a longer key is better.

## Implementation Features
1.	Usually the encryption output of any algorithm is in binary format, which any router / firewall in network path may detect and block. However, encryption output of this algorithm produces fully qualified UTF8 strings (encoding can be decided at key initialization time), which can be transmitted (over computer network) and / or stored (in files) electronically.


2.	Very low and fixed size memory and processing overhead. 


3.	Works on any computer architecture and operating system that supports C++/STL. It has been successfully tested on Intel 32bit, 64bit, ARM, ARM64, Linux, FreeBSD, Microsoft Windows and Apple Mac OSX.

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

To utilize the code in your own projects,

- include itv_character.h header file in your project,
- link it against itv.so. 

Example Makefile,

````
all:
    g++ -Wall -Werror -g -std=c++11 -c main.cpp
    g++ main.o -g -Wall -lstdc++ -lz -litv -o main

clean:
    rm -fr main main.o
````
Description of sources,

````
	itv.h / itv.cpp => defines an ITV record
	itv_table.h / itv_table.cpp => defines an ITV Table.
    itv_characters.h / itv_characters.cpp => implementation of Character Based ITV.
	itv_utils.h => defines some utility functions.
````

For reference implementation of Character Based ITV algorithm, include or read through,

````
	itv_characters.h / itv_characters.cpp
````

## Example Usage
Examples are available in various programming languages including C, C++, Perl, Python and PHP5.

### C++

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
    sender.load(0x20, 0x20, 1); /* Add space character */

    /* randomly shuffle IDs */
    sender.shuffle();

    /* ITV Table that receiver needs to decrypt data */
    std::string itv_table = sender.dump_table();

    /* ITV Table checksum, the receiver can check it to ensure
     * whether or not decryption will be successful before actual decryption
     */
    size_t sender_checksum = sender.checksum();

    /* sample text to encrypt, we are using UTF8 encoding here */
    std::string msg = "حفلة في مدينة تدمُر يحييها الموسيقي الروسي فاليري غيرغييف";

    cout << "Original: " << msg << endl;

    /* encrypt the text */
    std::string encrypted_text = sender.encode(msg);

    /* convert encrypted text to UTF8 and send it, here we just print it */
    cout << "Encrypted: " << encrypted_text << endl << endl;


    /* On Receiver side,
     * the ITV Table is initialised with table dump from sender side
     */
    ITV_Characters receiver = ITV_Characters(itv_table);

    /* ITV Table checksum, if this match's sender checksum then ITV Table integrity is verified
     * and decryption will be successful
     */
    size_t receiver_checksum = receiver.checksum();

    if (receiver_checksum != sender_checksum) {
        cout << "Error: checksum mismatch" << endl;
        cout << "Local: 0x" << std::hex << receiver_checksum << endl;
        cout << "Remote: 0x" << std::hex << sender_checksum << endl;
        return 0;
    } else {
        cout << "ITV Table Integrity Verified: 0x" << std::hex << sender_checksum << endl;
    };

    std::string decrypted_text = receiver.decode(encrypted_text);

    if (msg == decrypted_text) {
        cout << "Decrypted: " << decrypted_text << endl;
    } else {
        cout << "Failure: " << decrypted_text << endl;
    };

    return 0;
};
````

Running the program gives something like,

````
Original: حفلة في مدينة تدمُر يحييها الموسيقي الروسي فاليري غيرغييف
Encrypted: քժՒדց׊գԭԐ֯דԉղ֯ղׯקՑԛת֯ה֏ԽԭԎׯԑյַתԅՑ֥ԶדռՍԑ֜הԇժԘԇ֚֚טֳԤԏԚ֜ԡԚՃ׊Ԍ֥֏Ԑם֫Դטԓ׋֋ԓբԡׯՃՋԌԭՍՙםԵԴ֫բԠׯգԉֿՋԋԭղԠ״ՙԷ״Ըգ֖Օ׷Ը׆Է՟׷ԋ׆ייւֿմ

ITV Table Integrity Verified: 0x38442
Decrypted: حفلة في مدينة تدمُر يحييها الموسيقي الروسي فاليري غيرغييف
````

Feel free to add and/or extend given C++ classes (per MPL v2.0 license).

### Perl
````perl
use strict;
use warnings;

use ITV;

my $msg = "پناہ گزینوں کے کیمپ پر حملہ جنگی جرم کے مترادف";

my $sender = ITV::ITV_Characters->new(0x100, 0x600, 0x1FF - 0x100);

my $sender_cs = $sender->shuffle();
my $key = $sender->dump_table();
my $enc = $sender->encode($msg);

print "Key: $key\nCS: $sender_cs\n\n";
print "MSG: $msg\nENC: $enc\n\n";

my $receiver = ITV::ITV_Characters->new($key);
my $receiver_cs = $receiver->checksum();

if ($sender_cs eq $receiver_cs) {
    print "Checksum OK: $receiver_cs\n";
} else {
    print "ERROR: Checksum Mismatch: $sender_cs != $receiver_cs\n";
    exit;
};

my $dec = $receiver->decode($enc);
print "DEC: $dec\n";

exit;
````

Running program gives something like,

````
MSG: پناہ گزینوں کے کیمپ پر حملہ جنگی جرم کے مترادف
ENC: ƍēƮŠǼŧƓƧ ęĺĵǉǛƉŠĖƎŧƳŅ ƘǙǲǟ ǙǻƉƵǂƷēŲ Ųƈƌƒ ƚǔƷǽœƘƧƝ ƂũĖƍĺŕƵņ ũŌƒƺǽǥ ǻĆǟĿ ǥŮưĎƺŵƎƤħƣǎƀ

Checksum OK: 489314
DEC: پناہ گزینوں کے کیمپ پر حملہ جنگی جرم کے مترادف
````

### Python
````python
import pyitv

# message to test encryption
msg = "A Quick Brown Fox Jumps Over The Lazy Dog.";

# sender object - initialized with all printable ASCII
src = pyitv.ITV_Characters(32, 32, 126 - 32)

# shuffle the table and get its checksum, the receiver can
# match it to confirm it has correct itv table for decryption
src_cs = src.shuffle()

# get the table, this will be required by receiver for decryption
key = src.dump_table()

# encrypt the message
enc = src.encode(msg)

# print it out
print "Key: %s\nCS: 0x%x\n\nMSG: %s\nENC: %s\n" % (key, src_cs, msg, enc)


# initialize receiver object with itv table sent by sender
dst = pyitv.ITV_Characters(key)

# verify we have correct table for decrpytion
dst_cs = dst.checksum()

if src_cs == dst_cs:
    print "Checksum OK: 0x%x" % (dst_cs)
else:
    print "ERROR: Checksum Mismatch: 0x%x != 0x%x" % (src_cs, dst_cs)

# decrypt the message
dec = dst.decode(enc)

# print it out
print "DEC: %s" % (dec)
````

Running program gives something like,
````
MSG: A Quick Brown Fox Jumps Over The Lazy Dog.
ENC: %jVvRQL\<SN?oBv!i%7u}Jf)Y2!1zHJt/w1mWq\R70{Q5=mCJ2eI|2utCs@<]r2!s`sH+.8|iL`uf;`U(*Fj

Checksum OK: 0x13b4
DEC: A Quick Brown Fox Jumps Over The Lazy Dog.
````


## About Author
The concept and sample code was developed by Muhammad Shahzad Shafi (shahzad at voip-demos dot com). The sample code is released under MPL v2.0 license.

The concept and sample code are intended for scientific research and peaceful means.
