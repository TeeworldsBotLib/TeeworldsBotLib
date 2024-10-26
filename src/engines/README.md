# engines

Engines are reusable parts of code that can be shared across multiple bots.
Engines do not inherit from the bot base but take a pointer to it. So they can be easily
plugged in to any bot.


If you have a reusable piece of code such as a path finder you can inherit from the base engine.
And then in your bot create an instance of your engine.

