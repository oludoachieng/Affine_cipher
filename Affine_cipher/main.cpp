#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include<time.h>


using namespace std;
/**This is the encryption function**/
int encrypt(int a, int x, int b) {
    int z = (a * x + b) % 26;
    return z;

}
/**This is the decryption function**/
int decrypt(int c, int x, int b) {
    int z = (c * (x - b)) % 26;

    return z;

}

int main()
{
    srand(time(0));//Generate a random no. for 2nd key


    /**ENCRYPTION**/

/**Error handling, check if there is a plain text and key.**/
    ifstream ifs2("plain.txt", ios::ate);
    if (ifs2.tellg() == 0)
    {
        cout << "The plain.txt file is empty, please input the plain text.";
        return 0;
    }
    ifstream ifs("key-encrypt.txt", ios::ate);
    if (ifs.tellg() == 0)
    {
        cout << "The key-encrypt.txt file is empty, please input the key.";
        return 0;
    }

    /**Next step is to grab the encryption key from "key-encrypt.txt" and store in key_vector**/
    ifstream key_input;
    key_input.open("key-encrypt.txt");
    char d;
    vector<int> key_vector;

    while (key_input >> d)
    {
        int key_int = static_cast<int>(d);
        /**I used only small letters so check if key is only small letters**/
        if (key_int < 97 || key_int>122)
        {
            cout << "Error:Key should be in small letters";
            return 0;
        }
        key_int -= 97;
        key_vector.push_back(key_int);
    }
    key_input.close();


    /**Next step is to check if a is relatively prime to 26, otherwise inverse will not exist**/
    if ((key_vector[0] % 2) == 0)
    {
        cout << "Error: Key has no inverse mod 26. Try a different key";
        return 0;
    }
    if (key_vector[0] == 13)
    {
        cout << "Error: Key has no inverse mod 26. Try a different key";
        return 0;
    }
    if (key_vector[0] == 0)
    {
        cout << "Error: Key has no inverse mod 26. Try a different key";
        return 0;
    }

    /**Next step is to find inverse of'a' mod 26 and save this together with the 'b' value as decryption key**/
    int inv;
    for (int f = 1; f < 26;f++)
    {
        if ((f * key_vector[0]) % 26 == 1)
            inv = f;
    }
    int inv_asc = inv + 97;
    int random = rand() % 26;
    key_vector.push_back(random);

    int beta = key_vector[1]+97;
    

    char inv_char1 = static_cast<char>(inv_asc);
    char inv_char2 = static_cast<char>(beta);
    ofstream write_decrypt_key;
    write_decrypt_key.open("key-decrypt.txt");

    write_decrypt_key << inv_char1 << inv_char2;
    write_decrypt_key.close();

    /**Next step is to encrypt the plain text using the keys given and the encrypt function we defined at the beginning**/
    ifstream plain_input;
    plain_input.open("plain.txt");
    char p;
    vector<char> ciph_vector;
    while (plain_input >> p)
    {
        int plain_char = static_cast<int>(p);
        /**I used only small letters so check if plain text is only small letters**/
        if (plain_char < 97 || plain_char>122)
        {
            cout << "Error:Plain text should be in small letters";
            return 0;
        }
        plain_char -= 97;
        int ciph = encrypt(key_vector[0], plain_char, key_vector[1]);//calling encrypt function
        ciph += 97;
        char ciph_char = static_cast<char>(ciph);
        ciph_vector.push_back(ciph_char);
    }
    plain_input.close();

    /**Next step is to save the encyption in cipher.txt**/
    ofstream write_ciph;
    write_ciph.open("cipher.txt");
    for (int vec_siz = 0; vec_siz != ciph_vector.size(); vec_siz++)
    {
        write_ciph << ciph_vector[vec_siz];
    }
    write_ciph.close();

    /**DECRYPTION**/
    /**We shall decrypt using the decrypt function defined at the beginning and the decryption keys we calculated*/
    ifstream cip_input;
    cip_input.open("cipher.txt");
    char q;
    vector<char> plain_vector;
    while (cip_input >> q)
    {
        int cip_val = static_cast<int>(q);
        cip_val -= 97;
        int plain = decrypt(inv, cip_val, key_vector[1]);//calling decrypt function

        if (plain < 0) {
            while (plain < 0)plain += 26;
        }
        if (plain > 25) {
            while (plain > 25)plain -= 26;
        }

        plain += 97;
        char plain_char = static_cast<char>(plain);
        plain_vector.push_back(plain_char);
    }
    cip_input.close();

    /**Save the decryption in the plaintext.txt file**/
    ofstream write_plain;
    write_plain.open("plaintext.txt");
    for (int vec2_siz = 0; vec2_siz != plain_vector.size(); vec2_siz++)
    {
        write_plain << plain_vector[vec2_siz];
    }
    write_plain.close();

    /**END OF DECRYPTION**/
    cout << endl;
    cout << "ENCRYPTION AND DECRYPTION COMPLETE!";
    return 0;
}
