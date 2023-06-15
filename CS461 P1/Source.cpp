#include <iostream>
#include <vector>
#include <random>
#include<algorithm>
#include <fstream>
using namespace std;

//Using a struct to be able to better organize the cards
struct Card 
{
    char suit, face;
    Card(char aSuit, char aFace) : suit(aSuit), face(aFace) { }
};

int CardRank(vector<Card>& hand);

bool P1Win(int P1, int P2, int P3, int P4, int P5, int P6);

int main() 
{
    //Initializing the deck of cards and Adding the cards themselves
    const int numSuits = 4;
    const int numFaces = 13;
    const int deckSize = 52;
    vector<Card> deck;
    char suit[numSuits] = { 'H','D','C','S' };
    char face[numFaces] = { '2','3','4','5','6','7','8','9','T','J','Q','K','A' };

    // initalizing the players, winner, scores and the card ranks
    vector<Card> P1, P2, P3, P4, P5, P6;
    int P1Score, P2Score, P3Score, P4Score, P5Score, P6Score;
    float highCard = 0, onePair = 0, twoPair = 0, threeKind = 0, normalStright = 0, Flush = 0, fourKind = 0, straightFlush = 0, royalFlush = 0, fullHouse = 0;
    float highCardWin = 0, onePairWin = 0, twoPairWin = 0, threeKindWin = 0, normalStrightWin = 0, FlushWin = 0, fourKindWin = 0, straightFlushWin = 0, royalFlushWin = 0, fullHouseWin = 0;
    float totalHands = 0;
    float totalHandsWin = 0;
    float totalHandPercent;
    float currentHand = 0;
    float currentHandWin = 0;
    float currentHandPercent;
    bool  win = false;

    //open the files to be written to 
    ofstream csvFile("PokerStats.csv");
    ofstream txtFile("PokerHands.txt");

    txtFile << "Rank           Rank Percent/Total Hands         Win Percent\n";
    csvFile << "Cards in Hand,Rank of Hand,Hand Winning Percent\n";

    // begin the game
    for (int i = 0; i < 1000; i++)
    {
        //fill the deck with cards
        for (int j = 0; j < 13; j++)
        {
            for (int i = 0; i < 4; i++)
            {
                deck.push_back(Card(suit[i], face[j]));
            }
        }

        std::random_shuffle(deck.begin(), deck.end());
        //Dealing player 1 their hands
        for (int i = 0; i < 5; i++)
        {
            P1.push_back(deck[i]);
        }
        P1Score = CardRank(P1);

        //remove player ones cards
        deck.erase(deck.begin(), deck.begin() + 5);

        //Dealing everyone else and determining the round winner
        for (int j = 0; j < 1000; j++)
        {
            win = false;
                        
            for (int i = 0; i < 5; i++)
            {
                P2.push_back(deck[i]);
            }
            P2Score = CardRank(P2);


            for (int i = 5; i < 10; i++)
            {
                P3.push_back(deck[i]);
            }
            P3Score = CardRank(P3);

            for (int i = 10; i < 15; i++)
            {
                P4.push_back(deck[i]);
            }
            P4Score = CardRank(P4);

            for (int i = 15; i < 20; i++)
            {
                P5.push_back(deck[i]);
            }
            P5Score = CardRank(P5);

            for (int i = 20; i < 25; i++)
            {
                P6.push_back(deck[i]);
            }
            P6Score = CardRank(P6);

            currentHand++;
            totalHands++;
            win = P1Win(P1Score, P2Score, P3Score, P4Score, P5Score, P6Score);
            if (win == true)
            {
                currentHandWin += 1;
            }
            P2.clear();
            P3.clear();
            P4.clear();
            P5.clear();
            P6.clear();
            std::random_shuffle(deck.begin(), deck.end());
            
        }
        
        //clear hands for next round
        currentHandPercent = currentHandWin / currentHand;
        deck.clear();
        currentHand = 0;
        currentHandWin = 0;

        for (const auto arr : P1)
        {
            csvFile << arr.suit << arr.face << " ";
        }

        if (P1Score == 1)
        {
            highCard += 1;
            if (win == true)
            {
                highCardWin += 1;
            } 
            csvFile << ",High Card," << currentHandPercent << "\n";

        }
        else if (P1Score == 2)
        {
            onePair += 1;
            if (win == true)
            {
                onePairWin += 1;
            }
            csvFile << ",One Pair," << currentHandPercent << "\n";

        }
        else  if (P1Score == 3)
        {
            twoPair += 1;
            if (win == true)
            {
                twoPairWin += 1;
            }
            csvFile << ",Two Pair," << currentHandPercent << "\n";

        }
        else if (P1Score == 4)
        {
            threeKind += 1;
            if (win == true)
            {
                threeKindWin += 1;
            }
            csvFile << ",Three of A Kind," << currentHandPercent << "\n";

        }
        else if (P1Score == 5)
        {
            normalStright += 1;
            if (win == true)
            {
                normalStrightWin += 1;
            }
            csvFile << ",Straight," << currentHandPercent << "\n";

            
        }
        else if (P1Score == 6)
        {
            Flush += 1;
            if (win == true)
            {
                FlushWin += 1;
            }
            csvFile << ",Flush," << currentHandPercent << "\n";

        }
        else if (P1Score == 7)
        {
            fullHouse += 1;
            if (win == true)
            {
                fullHouseWin += 1;
            }
            csvFile << ",Full House," << currentHandPercent << "\n";

        }
        else if (P1Score == 8)
        {
            fourKind += 1;
            if (win == true)
            {
                fourKindWin += 1;
            }
            csvFile << ",Four of a Kind," << currentHandPercent << "\n";

        }
        else if (P1Score == 9)
        {
            straightFlush += 1;
            if (win == true)
            {
                straightFlushWin += 1;
            }
            csvFile << ",Straight Flush," << currentHandPercent << "\n";

        }
        else if (P1Score == 10)
        {
            royalFlush += 1;
            if (win == true)
            {
                royalFlushWin += 1;
            }
            csvFile << ",Royal Flush," << currentHandPercent << "\n";

        }

        P1.clear();
    }
   
    totalHandPercent = totalHandsWin / totalHands;
    txtFile << "Royal Flush           ";
    if (royalFlush != 0)
    {
        txtFile << royalFlush / totalHands << "\t\t\t\t\t\t\t\t\t\t" << royalFlushWin / royalFlush;
    }
    else
    {
        txtFile << royalFlush/totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nStraigh Flush         ";
    if (straightFlush != 0)
    {
        txtFile << straightFlush / totalHands << "\t\t\t\t\t\t\t" << straightFlushWin / straightFlush;
    }
    else
    {
        txtFile << straightFlush / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nFour of a Kind        ";
    if (fourKind != 0)
    {
        txtFile << fourKind / totalHands << "\t\t\t\t\t\t\t" << fourKindWin / fourKind;
    }
    else
    {
        txtFile << fourKind / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nFull House            ";
    if (fullHouse != 0)
    {
        txtFile << fullHouse / totalHands << "\t\t\t\t\t\t\t\t\t\t" << fullHouseWin / fullHouse;
    }
    else
    {
        txtFile << royalFlush / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nFlush                 ";
    if (Flush != 0)
    {
        txtFile << Flush / totalHands << "\t\t\t\t\t\t\t" << FlushWin / Flush;
    }
    else
    {
        txtFile << Flush / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nStraight              ";
    if (normalStright != 0)
    {
        txtFile << normalStright / totalHands << "\t\t\t\t\t\t\t" << normalStrightWin / normalStright;
    }
    else
    {
        txtFile << normalStright / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nThree of a Kind       ";
    if (threeKind != 0)
    {
        txtFile << threeKind / totalHands << "\t\t\t\t\t\t" << threeKindWin / threeKind;
    }
    else
    {
        txtFile << threeKind / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nTwo Pair              ";
    if (twoPair != 0)
    {
        txtFile << twoPair / totalHands << "\t\t\t\t\t\t" << twoPairWin / twoPair;
    }
    else
    {
        txtFile << twoPair / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nOne Pair              ";
    if (onePair != 0)
    {
        txtFile << onePair / totalHands << "\t\t\t\t\t\t" << onePairWin / onePair;
    }
    else
    {
        txtFile << onePair / totalHands << "\t\t\t\t\t\t\t\tN/A";
    }
    txtFile << "\nHigh Card             ";
    if (highCard != 0)
    {
        txtFile << highCard / totalHands << "\t\t\t\t\t\t" << highCardWin / highCard;
    }
    else
    {
        txtFile << highCardWin / highCard << "\t\t\t\t\t\t\t\tN/A";
    }

    csvFile.close();
    txtFile.close();
	return  0;
}

bool P1Win(int P1, int P2, int P3, int P4, int P5, int P6)
{
    if ((P1 >= P2) && (P1 >= P3) && (P1 >= P4) && (P1 >= P5) && (P1 >= P6))
    {
        return  true;
    }
    else
    {
        return  false;
    }
}

int CardRank(vector<Card>& hand)
{
   
    int spade = 0;
    int club = 0;
    int heart = 0;
    int diamond = 0;
    int faceA = 0;
    int faceK = 0;
    int faceQ = 0;
    int faceJ = 0;
    int faceT = 0;
    int face9 = 0;
    int face8 = 0;
    int face7 = 0;
    int face6 = 0;
    int face5 = 0;
    int face4 = 0;
    int face3 = 0;
    int face2 = 0;
    int royal = 0;
    int pairs = 0;
    int triples = 0;
    bool flushCheck = false;
    //get the count of the faces and suits to know what is worth checking
    for (const auto& arr : hand)
    {
        if (arr.suit == 'S')
        {
            spade++;
        }
        else if (arr.suit == 'D')
        {
            diamond++;
        }
        else if (arr.suit == 'H')
        {
            heart++;
        }
        else if (arr.suit == 'C')
        {
            club++;
        }
        if (arr.face == 'A')
        {
            faceA++;
            royal++;
        }
        else if (arr.face == 'K')
        {
            faceK++;
            royal++;
        }
        else if (arr.face == 'Q')
        {
            faceQ++;
            royal++;

        }
        else if (arr.face == 'J')
        {
            faceJ++;
            royal++;
        }
        else if (arr.face == '10')
        {
            faceT++;
            royal++;
        }
        else if (arr.face == '9')
        {
            face9++;
        }
        else if (arr.face == '8')
        {
            face8++;
        }
        else if (arr.face == '7')
        {
            face7++;
        }
        else if (arr.face == '6')
        {
            face6++;
        }
        else if (arr.face == '5')
        {
            face5++;
        }
        else if (arr.face == '4')
        {
            face4++;
        }
        else if (arr.face == '3')
        {
            face3++;
        }
        else if (arr.face == '2')
        {
            face2++;
        }
    }
    //checks for royal flush, straight flush or a regular flush if all suits are the same
    if (spade == 5 || diamond == 5 || club == 5 || heart == 5)
    {
        flushCheck = true;
        //royal
        if (royal == 5)
        {
            return  10;
        }
        //flush
        else
        {
            return  6;
        }
    }
    //checking for a straight
    if (faceK == 1 && faceQ == 1 && faceJ == 1 && faceT == 1 && face9 == 1)
    {
        return 9;
    }
    else if (faceQ == 1 && faceJ == 1 && faceT == 1 && face9 == 1 && face8 == 1)
    {
        return 9;
    }
    else if (faceJ == 1 && faceT == 1 && face9 == 1 && face8 == 1 && face7 == 1)
    {
        return 9;
    }
    else if (faceT == 1 && face9 == 1 && face8 == 1 && face7 == 1 && face6 == 1)
    {
        return 9;
    }
    else if (face9 == 1 && face8 == 1 && face7 == 1 && face6 == 1 && face5 == 1)
    {
        return 9;
    }
    else if (face5 == 1 && face4 == 1 && face3 == 1 && face2 == 1 && faceA == 1)
    {
        return 9;
    }
    //checks 4 of a kind
    if (face2 == 4)
    {
        return 8;
    }
    if (face3 == 4)
    {
        return 8;
    }
    if (face4 == 4)
    {
        return 8;
    }
    if (face5 == 4)
    {
        return 8;
    }
    if (face6 == 4)
    {
        return 8;
    }
    if (face7 == 4)
    {
        return 8;
    }
    if (face8 == 4)
    {
        return 8;
    }
    if (face9 == 4)
    {
        return 8;
    }
    if (faceT == 4)
    {
        return 8;
    }
    if (faceJ == 4)
    {
        return 8;
    }
    if (faceQ == 4)
    {
        return 8;
    }
    if (faceK == 4)
    {
        return 8;
    }
    if (faceA == 4)
    {
        return 8;
    }
    //check for pairs
    if (face2 == 2)
    {
        pairs++;
    }
    if (face3 == 2)
    {
        pairs++;
    }
    if (face4 == 2)
    {
        pairs++;
    }
    if (face5 == 2)
    {
        pairs++;
    }
    if (face6 == 2)
    {
        pairs++;
    }
    if (face7 == 2)
    {
        pairs++;
    }
    if (face8 == 2)
    {
        pairs++;
    }
    if (face9 == 2)
    {
        pairs++;
    }
    if (faceT == 2)
    {
        pairs++;
    }
    if (faceJ == 2)
    {
        pairs++;
    }
    if (faceQ == 2)
    {
        pairs++;
    }
    if (faceK == 2)
    {
        pairs++;
    }
    if (faceA == 2)
    {
        pairs++;
    }
    //check for triples
    if (face2 == 3)
    {
        triples++;
    }
    if (face3 == 3)
    {
        triples++;
    }
    if (face4 == 3)
    {
        triples++;
    }
    if (face5 == 3)
    {
        triples++;
    }
    if (face6 == 3)
    {
        triples++;
    }
    if (face7 == 3)
    {
        triples++;
    }
    if (face8 == 3)
    {
        triples++;
    }
    if (face9 == 3)
    {
        triples++;
    }
    if (faceT == 3)
    {
        triples++;
    }
    if (faceJ == 3)
    {
        triples++;
    }
    if (faceQ == 3)
    {
        triples++;
    }
    if (faceK == 3)
    {
        triples++;
    }
    if (faceA == 3)
    {
        triples++;
    }
    //check for a full house
    if (pairs == 1 && triples == 1)
    {
        return 7;
    }
    //check triple 
    else if (triples == 1)
    {
        return 4;
    }
    // Check for 2 pairs
    else if (pairs == 2)
    {
        return 3;
    }
    //Check for a pair
    else if (triples != 1 && pairs == 1)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}
