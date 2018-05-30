# PrisonersDilemmaThesis
Iterated prisoners dilemma in C++. Agents percieve more loss than they actually have. I investigated to see if this creates cyclical stock market bubble like behavior. It doesn't.

## Procedure

"Players" (Simulated players) will play prisoners dilemma according to these payoffs.

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide11.png" width="400"/>

People *feel* more loss from missing gain than from loss. So let the agents feel this loss as well.  

If players play to 'inflate' their stock price: they cooperate to simulate the creation of a market bubble. They inflate their assets with each trade, adding to their perception of gain.

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide12.png" width="400"/>


So let's look at an example trade:

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide13.png" width="400"/>

Players prepare their strategies.

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide14.png" width="400"/>

One trade in the agent pool:

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide15.png" width="400"/>

Trade with all nearest neighors:

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide16.png" width="400"/>

Select the next agent and continue trading:

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide17.png" width="400"/>

Conduct these trades through all agents.

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide18.png" width="400"/>

Kill off a few agents, then allow the most successful agents to replicate their strategy.

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide19.png" width="400"/>

## Results

While we initially expected the models to cycle, they instead stablized. Here we graph all the strategies found at each different payout.

The only bubble-like behavior is near the boundary between two strategies:

<img src="img/PreGamingPresentationPhilipGeurinAugest2010d/Slide22.png" width="400"/>

## Questions? Reach out!

![contact_philipgeurin.png](img/contact_philipgeurin.png)
