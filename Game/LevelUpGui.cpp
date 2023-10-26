#include "LevelUpGui.h"

LevelUpGui::LevelUpGui(sf::RenderWindow& window,Ability* ability,int abilityCanlevelup1, int abilityCanlevelup2)
{
	this->ability = ability;
	this->abilityCanlevelup1 = abilityCanlevelup1;
	this->abilityCanlevelup2 = abilityCanlevelup2;
	if (!font.loadFromFile("Resource/font/Pixelpoint.ttf")) {
		std::cerr << "Error loading font!" << std::endl;
	}

	levelUpText.setFont(font);
	levelUpText.setCharacterSize(60);
	levelUpText.setFillColor(sf::Color::Black);
	levelUpText.setString("Level Up!");
	levelUpText.setOrigin(levelUpText.getGlobalBounds().width / 2, levelUpText.getGlobalBounds().height / 2);
	
	levelUpBackground.setFillColor(sf::Color::Color(255, 255, 255, 200));
	levelUpBackground.setSize(sf::Vector2f(500.0f, 600.0f));
	levelUpBackground.setOrigin(levelUpBackground.getGlobalBounds().width / 2, levelUpBackground.getGlobalBounds().height / 2);

	selectText1.setFont(font);
	selectText1.setCharacterSize(30);
	selectText1.setFillColor(sf::Color::Black);
	selectText1.setString("Select");
	selectText1.setOrigin(selectText1.getGlobalBounds().width / 2, selectText1.getGlobalBounds().height / 2);

	selectText2.setFont(font);
	selectText2.setCharacterSize(30);
	selectText2.setFillColor(sf::Color::Black);
	selectText2.setString("Select");
	selectText2.setOrigin(selectText2.getGlobalBounds().width / 2, selectText2.getGlobalBounds().height / 2);
	
	Button1.setFillColor(sf::Color::Red);
	Button2.setFillColor(sf::Color::Red);
}

void LevelUpGui::Render(sf::RenderWindow& window)
{
	window.draw(levelUpBackground);
	window.draw(informationText1);
	window.draw(informationText2);
	window.draw(sprite1);
	window.draw(sprite2);
	window.draw(Button1);
	window.draw(Button2);
	window.draw(selectText1);
	window.draw(selectText2);
	window.draw(levelUpText);
}

void LevelUpGui::setPosition(const sf::Vector2f& playerPos)
{
	float xOffset = 0.0f;
	float yOffset = 250.0f;

	setInformationText1();
	setInformationText2();

	levelUpText.setPosition(playerPos.x , playerPos.y-yOffset);
	levelUpBackground.setPosition(playerPos.x , playerPos.y );

	informationText1.setPosition(levelUpText.getPosition().x, levelUpText.getPosition().y + 150.0f);
	informationText2.setPosition(informationText1.getPosition().x, informationText1.getPosition().y + 200.0f);

	sprite1.setPosition(informationText1.getPosition().x -200, informationText1.getPosition().y);
	sprite2.setPosition(informationText2.getPosition().x -200, informationText2.getPosition().y );

	Button1.setSize(sf::Vector2f(100.0f, 50.0f));
	Button1.setPosition(sprite1.getPosition().x + 150.0f, sprite1.getPosition().y + 80.0f);

	Button2.setSize(sf::Vector2f(100.0f, 50.0f));
	Button2.setPosition(sprite2.getPosition().x + 150.0f, sprite2.getPosition().y + 80.0f);

	selectText1.setPosition(Button1.getPosition().x + 50.0f, Button1.getPosition().y + 10.0f);
	selectText2.setPosition(Button2.getPosition().x + 50.0f, Button2.getPosition().y + 10.0f);


}

void LevelUpGui::setInformationText1()
{
	bool checkNewAbility = true;
	if (abilityCanlevelup1 == 0) {
		for (int i = 0; i < 3; i++) {
			if (ability[i].getType() == AbilityType::FireBall)
			{
				texture1.loadFromFile("Resource/sprite/Item/FireBallAbility.png");
				sprite1.setTexture(texture1);
				sprite1.setScale(0.4f, 0.4f);

				if (ability[i].abilityInfo.level == 1)
					informationText1.setString("Level 2: \nBase Damage: 200");
				if (ability[i].abilityInfo.level == 2)
					informationText1.setString("Level 3: \nAmount: 2");
				if (ability[i].abilityInfo.level == 3)
					informationText1.setString("Level 4: \nBase Damage: 300");
				if (ability[i].abilityInfo.level == 4)
					informationText1.setString("Level 5: \nAmount: 3");
				if (ability[i].abilityInfo.level == 5)
					informationText1.setString("Level 6: \nBase Damage: 400");
				if (ability[i].abilityInfo.level == 6)
					informationText1.setString("Level 7: \nAmount: 4");
				informationText1.setFont(font);
				informationText1.setCharacterSize(30);
				informationText1.setFillColor(sf::Color::Black);
				informationText1.setOrigin(informationText1.getGlobalBounds().width / 2, informationText1.getGlobalBounds().height / 2);
				checkNewAbility = false;
			}
		}
		if (checkNewAbility) {
			informationText1.setString("New Ability: \nFireBall");
		}

	}

	if (abilityCanlevelup1 == 1) {
		for (int i = 0; i < 3; i++) {
			if (ability[i].getType() == AbilityType::CircleDamage) {

				texture1.loadFromFile("Resource/sprite/Item/Circle.png");
				sprite1.setTexture(texture1);
				sprite1.setScale(0.4f, 0.4f);

				if (ability[i].abilityInfo.level == 1)
					informationText1.setString("Level 2: \nAmount: 2\nRadius: 120");
				if (ability[i].abilityInfo.level == 2)
					informationText1.setString("Level 3: \nDuration: 2.5\nBase Damage: 110");
				if (ability[i].abilityInfo.level == 3)
					informationText1.setString("Level 4: \nAmount: 3\nRadius: 140");
				if (ability[i].abilityInfo.level == 4)
					informationText1.setString("Level 5: \nDuration: 3.0\nBase Damage: 120");
				if (ability[i].abilityInfo.level == 5)
					informationText1.setString("Level 6: \nAmount: 4\nRadius: 160");
				if (ability[i].abilityInfo.level == 6)
					informationText1.setString("Level 7: \nDuration: 3.5\nBase Damage: 130");
				informationText1.setFont(font);
				informationText1.setCharacterSize(30);
				informationText1.setFillColor(sf::Color::Black);
				informationText1.setOrigin(informationText1.getGlobalBounds().width / 2, informationText1.getGlobalBounds().height / 2);
				checkNewAbility = false;
			}
		}
		if (checkNewAbility) {

			texture1.loadFromFile("Resource/sprite/Item/Circle.png");
			sprite1.setTexture(texture1);
			sprite1.setScale(0.4f, 0.4f);
			informationText1.setFont(font);
			informationText1.setCharacterSize(30);
			informationText1.setFillColor(sf::Color::Black);
			informationText1.setOrigin(informationText1.getGlobalBounds().width / 2, informationText1.getGlobalBounds().height / 2);
			informationText1.setString("New Ability: \nCircle Damage");
		}

	}

}

void LevelUpGui::setInformationText2()
{
	bool checkNewAbility = true;
	if (abilityCanlevelup2 == 0) {
		for (int i = 0; i < 3; i++) {
			if (ability[i].getType() == AbilityType::FireBall)
			{
				texture2.loadFromFile("Resource/sprite/Item/FireBallAbility.png");
				sprite2.setTexture(texture2);
				sprite2.setScale(0.4f, 0.4f);

				if (ability[i].abilityInfo.level == 1)
					informationText2.setString("Level 2: \nBase Damage: 200");
				if (ability[i].abilityInfo.level == 2)
					informationText2.setString("Level 3: \nAmount: 2");
				if (ability[i].abilityInfo.level == 3)
					informationText2.setString("Level 4: \nBase Damage: 300");
				if (ability[i].abilityInfo.level == 4)
					informationText2.setString("Level 5: \nAmount: 3");
				if (ability[i].abilityInfo.level == 5)
					informationText2.setString("Level 6: \nBase Damage: 400");
				if (ability[i].abilityInfo.level == 6)
					informationText2.setString("Level 7: \nAmount: 4");
				informationText2.setFont(font);
				informationText2.setCharacterSize(30);
				informationText2.setFillColor(sf::Color::Black);
				informationText2.setOrigin(informationText2.getGlobalBounds().width / 2, informationText2.getGlobalBounds().height / 2);
				checkNewAbility = false;
			}
		}
		if (checkNewAbility) {
			informationText2.setString("New Ability: \nFireBall");
		}
	}
	if(abilityCanlevelup2 == 1)
		for (int i = 0; i < 3; i++) {
			if (ability[i].getType() == AbilityType::CircleDamage) {

				texture2.loadFromFile("Resource/sprite/Item/Circle.png");
				sprite2.setTexture(texture2);
				sprite2.setScale(0.4f, 0.4f);

				if (ability[i].abilityInfo.level == 1)
					informationText2.setString("Level 2: \nAmount: 2\nRadius: 120");
				if (ability[i].abilityInfo.level == 2)
					informationText2.setString("Level 3: \nDuration: 2.5\nBase Damage: 110");
				if (ability[i].abilityInfo.level == 3)
					informationText2.setString("Level 4: \nAmount: 3\nRadius: 140");
				if (ability[i].abilityInfo.level == 4)
					informationText2.setString("Level 5: \nDuration: 3.0\nBase Damage: 120");
				if (ability[i].abilityInfo.level == 5)
					informationText2.setString("Level 6: \nAmount: 4\nRadius: 160");
				if (ability[i].abilityInfo.level == 6)
					informationText2.setString("Level 7: \nDuration: 3.5\nBase Damage: 130");
				informationText2.setFont(font);
				informationText2.setCharacterSize(30);
				informationText2.setFillColor(sf::Color::Black);
				informationText2.setOrigin(informationText2.getGlobalBounds().width / 2, informationText2.getGlobalBounds().height / 2);
				checkNewAbility = false;
			}
		}

	if (checkNewAbility) {
		texture2.loadFromFile("Resource/sprite/Item/Circle.png");
		sprite2.setTexture(texture2);
		sprite2.setScale(0.4f, 0.4f);
		informationText2.setFont(font);
		informationText2.setCharacterSize(30);
		informationText2.setFillColor(sf::Color::Black);
		informationText2.setOrigin(informationText2.getGlobalBounds().width / 2, informationText2.getGlobalBounds().height / 2);
		informationText2.setString("New Ability: \nCircle Damage");
	}
	
}

bool LevelUpGui::isPressButton1(sf::Vector2f mosuePos)
{
	std::cout << Button1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos)) << std::endl;
	return Button1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos));
}

bool LevelUpGui::isPressButton2(sf::Vector2f mosuePos)
{
	return Button2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos));
}

void LevelUpGui::isHoverButton2(sf::Vector2f mosuePos)
{
	if (Button2.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
		Button2.setFillColor(sf::Color::Green);
	}
	else {
		Button2.setFillColor(sf::Color::Red);
	}
}

void LevelUpGui::isHoverButton1(sf::Vector2f mosuePos)
{
	if (Button1.getGlobalBounds().contains(static_cast<sf::Vector2f>(mosuePos))) {
		Button1.setFillColor(sf::Color::Green);
	}
	else {
		Button1.setFillColor(sf::Color::Red);
	}
}
