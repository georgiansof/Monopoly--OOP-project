/*if(keycode == Keyboard::Key::Enter) {
        Player *currentPlayer = *currentPlayerIterator;
        cout << currentPlayer->getName() << "'s turn: \n";
        cout << "Position before: " << currentPlayer->getBoardPosition() << '\n';
        pair<uint8_t,uint8_t> dices;
        uint8_t timesRolledDouble = 0;
        int totalMoved = 0;
        do {
            dices = Game::diceRoll();
            if (dices.first == dices.second && timesRolledDouble == 2) {
                timesRolledDouble = 3;
                ///jail player
            }
            else {
                if (dices.first == dices.second)
                    ++timesRolledDouble;
                board.getTile(currentPlayer->getBoardPosition()).removePlayer(currentPlayer->getIndexInsideTile());
                auto updatedPosition = currentPlayer->incrementPosition(dices.first + dices.second);
                totalMoved += (dices.first + dices.second);
                auto newPositionInsideTile = board.getTile(updatedPosition.first).addPlayer(currentPlayer);
                currentPlayer->indexInsideTile = newPositionInsideTile.second;
                newPositionInsideTile.first.x *= (float)this->getWindowSize().x;
                newPositionInsideTile.first.y *= (float)this->getWindowSize().y;
                currentPlayer->boardPieceShapePtr->setPosition(newPositionInsideTile.first);

                if(updatedPosition.second) /// went through start
                    currentPlayer->money += MONEY_FROM_START;
            }
        }
        while(dices.first == dices.second && timesRolledDouble < 3);
        cout << "Total tiles moved: " << totalMoved << '\n';
        cout << "Position after: " << currentPlayer->getBoardPosition() << '\n';
        ++currentPlayerIterator;

    }*/