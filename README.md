# WhiteRunner
White Runner is a bot that collects grey/white items from the templar side story quest. It then salvages these grey items giving the player grey materials for use in crafting, enchanting, or upgrading items. White Runners intended use is to gather white materials and use Kanai's Cube to convert white materials to blue and yellow materials. We then can use Kanai's Cube again to upgrade a rare item into a legendary item with blue, yellow, and white materials. This saves the player time of having grind endlessly for the legendary item or for materials to do the upgrade.

White Runner makes use of image processing and memory reading. The image processing is for simple tasks such as clicking on action buttons like the "leave game" and "ok" button presented during its loops through the game. While the memory reading is for more complex tasks such as finding chests, looting, and verifying states of looted chests.

# Status (28/12/2017): In-Progress
White Runner is now split up into individual files for better flow and testing of bot functunality.

<a href="http://www.youtube.com/watch?feature=player_embedded&v=Wsy5g44H9FU
" target="_blank"><img src="http://img.youtube.com/vi/Wsy5g44H9FU/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

(For reference here is the previouse video: <https://youtu.be/YejSuaRm38c>)

The next step for White Runner is improving the navigation between objectives, ideally this would be through nav meshes built from the in-game meshes. I also want to redo the template function as the number of parameters is getting out of hand. As the bot is now using memory reading I would like to emphasizes the [disclaimer](https://github.com/Per-Plex/WhiteRunner#disclaimer) at the bottom of this README.

# Usage
The bot works with the most recent verision of Diablo 3 x64 game. To run it you must have The Templars Quest available and have the templar as your follower. Once you have verified the prerequisites mentioned exit into the mode selection lobby and run the main.cpp file. It should handle everything from there.

# Disclaimer
This code is not intended for distribution or usage during season for Diablo 3. This code is to be for **educational purposes only**. I have not and will not use it for advantageous reasons against other players in Diablo 3.
