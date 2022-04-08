
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;


const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};


void shuffle(int cards[])
{
  int card = 0, temp = 0;
  for(int i = 0; i < 52; i++)
  {
    cards[i] = i;
  }
  for(int i = 51; i > 0; i--)
  {
    card = rand() % (i + 1);
    temp = cards[card];
    cards[card] = cards[i];
    cards[i] = temp;
  }

}


void printCard(int id)
{
  /******** You complete ****************/
  cout << type[id%13] << "-" << suit[id/13] << " "; 
}


int cardValue(int id)
{
  id = value[id%13];

  return id;


}

void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for(int i = 0; i < numCards; i++)
  {
    printCard(hand[i]);
  }
  cout << "\0";

}


int getBestScore(int hand[], int numCards)
{
  int sum = 0, aceCounter = 0;
  for(int i = 0; i < numCards; i++)
  {
    if(hand[i] == 11)
    {
      aceCounter++;
    }
    sum += hand[i];
    if(sum > 21 && aceCounter >= 1)
    {
      sum -= 10;
      aceCounter--;
    }
  }

  return sum;
}

int main(int argc, char* argv[])
{

  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[NUM_CARDS];
  int dhand[9];
  int phand[9];


  int hand[21];
  int psum[21];
  int dsum[21];

  bool hit = false;
  char playerDecision = 's';
  char keepPlaying = 'y';

  while(keepPlaying != 'n')
  {
    int numCards = 0, playerSum = 0, dealerSum = 0, playerCards = 0, dealerCards = 0;
    bool dealerHit = false;
    shuffle(cards);
    for(int i = 0; i < 4; i++)
    {
      if(i%2 == 0)
      {
        phand[playerCards] = cards[i];
        psum[playerCards] = cardValue(cards[i]);
        playerCards++;
      }
      else
      {
        dhand[dealerCards] = cards[i];
        dsum[dealerCards] = cardValue(cards[i]);
        dealerCards++;
      }
    }
    numCards += 4;
    playerSum = getBestScore(psum, playerCards);
    dealerSum = getBestScore(dsum, dealerCards);
    cout << "Dealer: ";
    for(int i = 0; i < 2; i++)
    {
      if(i == 0)
      {
        cout << "? ";
      }
      else
      {
        printCard(dhand[i]);
      }
    }
    cout << endl;

    cout << "Player: ";
    for(int i = 0; i < 2; i++)
    {
      printCard(phand[i]);
    }
    cout << endl;

    if(playerSum != 21)
    {
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> playerDecision;
    }
    if(playerDecision != 'h' && playerDecision != 's')
    {
      return 0;
    }

    while(playerDecision == 'h')
    {
      hit = true;
      for(int i = playerCards; i < playerCards+1; i++, numCards++)
      {
        phand[i] = cards[numCards];
        psum[i] = cardValue(cards[numCards]);
      }
      playerCards++;
      for(int i = 0; i < playerCards; i++)
      {
        hand[i] = phand[i];
      }
      cout << "Player: ";
      printHand(hand, playerCards);
      cout << endl;
      playerSum = getBestScore(psum, playerCards);

      if(playerSum > 21)
      {
        cout << "Player busts" << endl;
        cout << "Lose " << playerSum << " " << dealerSum << endl;
        break;
      }
      else if(playerSum == 21)
      {
        playerDecision = 's';
        break;
      }

      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> playerDecision;
    }

    while(dealerSum < 17 && playerDecision == 's')
    {
      dealerHit = true;
      for(int i = dealerCards; i < dealerCards+1; i++, numCards++)
      {
        dhand[i] = cards[numCards];
        dsum[i] = cardValue(cards[numCards]);
      }
      dealerCards++;
      dealerSum = getBestScore(dsum, dealerCards);
      if(dealerSum >= 17)
      {
        for(int i = 0; i < dealerCards; i++)
        {
          hand[i] = dhand[i];
        }
        cout << "Dealer: ";
        printHand(hand, dealerCards);
        cout << endl;
        if(dealerSum > 21)
        {
          cout << "Dealer busts" << endl;
          cout << "Win " << playerSum << " " << dealerSum << endl;
          break;
        }
        else if(dealerSum > playerSum)
        {
         cout << "Lose " << playerSum << " " << dealerSum << endl;
         break;
        }
        else if(dealerSum < playerSum)
        {
         cout << "Win " << playerSum << " " << dealerSum << endl;
         break;
        }
        else
        {
          cout << "Tie " << playerSum << " " << dealerSum << endl;
          break;
        }
      }
    }

    if(dealerSum >= 17 && playerSum <= 21 && !dealerHit)
    {
      for(int i = 0; i < dealerCards; i++)
      {
        hand[i] = dhand[i];
      }
      cout << "Dealer: ";
      printHand(hand, dealerCards);
      cout << endl;
      if(dealerSum > playerSum)
      {
        cout << "Lose " << playerSum << " " << dealerSum << endl;
        cout << "\0";
      }
      else if(dealerSum < playerSum)
      {
        cout << "Win " << playerSum << " " << dealerSum << endl;
        cout << "\0";
      }
      else
      {
        cout << "Tie " << playerSum << " " << dealerSum << endl;
      }
    }

    cout << endl;
    cout << "Play again? [y/n]" << endl;
    cin >> keepPlaying;
    if(keepPlaying != 'y' && keepPlaying != 'n')
    {
      return 0;
    }
  }
  return 0;
}
