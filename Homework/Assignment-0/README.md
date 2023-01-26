# How I Cracked The Cipher

Following the hints given in the second class, I gave each letter in the ciphertext a number, either 1 or 2 to indicate and even or odd letter so I could easily identify which of the two sets of substitutions I would have to use for each one. 

From there, I started to look for words that I thought might be present in the ciphertext, the first of which was "cryptography". There was only one word long enough to be "cryptography" so I matched the characters in "cryptography" with the corresponding letter in the cipher. Then I filled in all of the corresponding letters throughout the rest of the ciphertext. The next word I used was "welcome" as the first word of the ciphertext was long enough to be "welcome" and it seemed like a kind way of greeting those who has figured out how to decrypt the assignment. 

From there I repeated the same process with a few other words that I thought might be present such as: "the", "assignment", and "due" since it had been mentioned that the due date was included in the encryption. 

Eventually I got to a point where I had enough letters filled in that I could start to make educated guesses as to what some of the other words might have been and filled in the missing letters from there as well as using the letters from those words in the other places that their encrypted version appeared.


# Ciphers used

Below are the substitutions that were used for decrypting the assignment, underscores in the plaintext row indicate that the corresponding letter was not present in the ciphertext.

### Odd Characters:
```
Ciphertext: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
Plaintext:  A G W _ B R N T X K H E D S _ M I O F U C _ P Y L _
```

### Even Characters:
```
Ciphertext: A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
Plaintext:  _ E _ H G W M C D U _ S L R K I _ T F A N Y _ O _ P
```

# Ciphertext:

```
CBYHRGL RR RKB SPFLH DRGLFRNJ XS RKPN HFVWRREFTWDX HRJFLL
SRN HDQL ALNPBUPBGR WMLTNB NJEGQR HDL ZYTQUHBIR RS HDQL
LUUNXZHPRU AL AU LGAPY TYXGE CPHD A LKXFR SPYB MBNHFPEPGE 
HDL HQZKBFL TLLI SXF RKB LUUNXZHPRU AUM DRF XXT HFTUOLI QR
HDQL ALNPBUPBGR QL MJL PG XGB PXGRK LHTFRQUB SFXP RRIAV
```

# Plaintext
```
WELCOME TO THE FIRST HOMEWORK OF THIS CRYPTOGRAPHY COURSE
FOR THIS ASSIGNMENT PLEASE SUBMIT THE PLAINTEXT OF THIS
ENCRYPTION AS AN EMAIL ALONG WITH A SHORT FILE DESCRIBING
THE CIPHERS USED FOR THE ENCRYPTION AND HOW YOU CRACKED IT
THIS ASSIGNMENT IS DUE IN ONE MONTH STARTING FROM TODAY
```