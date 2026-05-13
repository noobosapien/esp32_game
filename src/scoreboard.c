
#include <stdint.h>

#include <fonts.h>
#include <graphics.h>

#include "scoreboard.h"

SCOREBOARD scoreboard = {
    NULL, 0};

void update_scoreboard(GAME_CONFIG *game)
{
    if (!game->updated_scoreboard)
    {
        game->updated_scoreboard = true;

        SCORE *score = malloc(sizeof(SCORE));
        score->next_score = NULL;
        score->prev_score = NULL;
        score->score = game->score;

        // If there are no scores in the list add it as the first
        if (scoreboard.first_score == NULL)
        {
            scoreboard.first_score = score;
        }
        else
        {

            SCORE *last_score = scoreboard.first_score;

            while (true)
            {
                // If there is no score in the scoreboard add the score as the first score
                if (last_score->score > game->score && last_score->next_score)
                {
                    last_score = last_score->next_score;
                    continue;
                }
                else if (last_score->score < game->score) // If current score is more than previous score
                {
                    if (last_score->prev_score == NULL) // Case first score
                    {
                        scoreboard.first_score = score;
                        score->next_score = last_score;
                        last_score->prev_score = score;

                        scoreboard.amount += 1; // Increment the amount
                        break;
                    }
                    else // Case middle/end
                    {
                        score->prev_score = last_score->prev_score;
                        last_score->prev_score->next_score = score;
                        score->next_score = last_score;
                        last_score->prev_score = score;

                        scoreboard.amount += 1; // Increment the amount
                        break;
                    }
                }
                else if (last_score->score > game->score) // If current score is less than the previous score
                {
                    if (last_score->next_score)
                    {
                        last_score = last_score->next_score;
                        continue;
                    }
                    else // Swap with the previous score of the last score with the current score
                    {
                        last_score->next_score = score;
                        score->prev_score = last_score;
                        scoreboard.amount += 1;

                        break;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        prune_scoreboard(5); // Only store the first 5 scores
    }
}

void show_scoreboard(GAME_CONFIG *game)
{
    SCORE *last_score = scoreboard.first_score;
    int score_number = 1;

    setFont(FONT_SMALL);
    setFontColour(188, 165, 207);
    print_xy("Scoreboard (Top 5)", CENTER, LASTY + 25); // Show the heading

    while (last_score) // For all scores in the scoreboard show the score
    {
        setFont(FONT_SMALL);
        setFontColour(188, 165, 207);
        print_xy("Top score ", CENTER, LASTY + 15);
        gprintf("%d:  %d", score_number, last_score->score);
        score_number++;
        last_score = last_score->next_score;
    }
}

int get_num_scores()
{
    return scoreboard.amount; // Get the amount of scores in the scoreboard
}

void prune_scoreboard(int n)
{
    // Remove excess scores stored in the scoreboard
    while (scoreboard.amount >= n)
    {
        SCORE *last_score = scoreboard.first_score;

        while (last_score->next_score)
        {
            last_score = last_score->next_score;
        }

        if (last_score)
            remove_score(last_score);
    }
}

void remove_score(SCORE *score)
{
    // Remove a given score after setting its previous score-> next score to NULL
    score->prev_score->next_score = NULL;
    free(score);
    scoreboard.amount--;
}
