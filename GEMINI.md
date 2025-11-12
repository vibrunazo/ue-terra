# **Terra Arcana - Game Design Document **

**Working Title:** Terra Arcana *(Potential Subtitle: Spells, Titans, and Steel)*

## **1. Introduction & Vision**

**Concept:** Terra Arcana is an asynchronous PvP action RPG set in a high-fantasy version of modern Earth. Players engage in a unique cycle of creation and conquest: first, **anchoring a Lair** to a real-world location and **designing a powerful, AI-controlled Titan** to defend it. Then, **commanding a customizable, player-controlled Champion** in skill-based, top-down combat to **raid the Lairs of other players**, challenging their unique Titan creations even while they're offline.

**Core Experience:** The gameplay loop revolves around mastering two distinct skill sets: the strategic creativity of designing challenging Titan defenses with unique AI patterns, and the tactical prowess required to recognize and overcome the diverse, player-generated boss fights when attacking with a Champion. Victory relies on outsmarting opponents both on the drawing board and on the battlefield.

**Target Audience:** Players of action RPGs, boss-rush games, competitive PvP games, and creative building/strategy games who enjoy deep customization and skill-based challenges.

**Platform:** PC (Windows initially), potential for future console/mobile adaptation.

## **2. Gameplay**

### **2.1 Core Gameplay Loop**

The game revolves around two asynchronous phases:

1. **Defense (Titan Creation & Management):**  
   * Players design, customize, and deploy **Titans** – powerful, AI-controlled bosses – to defend Lairs anchored to specific real-world locations chosen by the player.  
   * Deep customization includes visual appearance (modular parts), stats, a unique loadout of abilities derived from player choices, and sophisticated AI attack patterns created using an in-game editor.  
   * Titans defend passively against attacks from other players even when the owner is offline. Players can watch replays of defensive battles to learn and improve their designs.  
2. **Attack (Champion Command):**  
   * Players recruit, train, and customize a roster of **Champions** – controllable hero units, led by the player's own Warlord character.  
   * Players select either their Warlord or another Champion from their roster and initiate raids against other players' Titans found on the world map.  
   * Combat is real-time, top-down action, emphasizing player skill in dodging, positioning, resource management, and **pattern recognition**.  
   * Defeating enemy Titans yields resources and ranking points. Attacking costs a limited resource ("Attack Tokens") to encourage meaningful attempts.

### **2.2 Combat Mechanics**

* **Viewpoint:** Top-down perspective.  
* **Controls:** Standard ARPG controls (e.g., WASD/Click-to-move, numbered ability keys, dodge button).  
* **Core Combat:** 1v1 Champion vs. AI-controlled Titan + potential minions.  
* **Skill Focus:** **Pattern Recognition.** Combat is designed as an "IQ Test." Titans execute complex, player-designed attack sequences ("patterns"). The attacker's primary skill is observing these patterns, forming hypotheses, testing them in real-time, and adapting their strategy to overcome the specific "puzzle" presented by each unique Titan. Execution (dodging, attacking) is crucial but secondary to understanding the pattern.  
* **Tells & Ambiguity:** Attacks have clear tells, ensuring **perfect tactical information** (no pure RNG determines hits). However, defenders can create **"fair ambiguity"** using shared wind-up animations with subtle, learnable differences ("Tell Tiers") or complex, reactive AI patterns, challenging the attacker's observation skills under pressure.  
* **Failure:** Getting hit by unknown patterns is expected and part of the learning process (the "cost of information"). Damage is tuned so single mistakes are generally not fatal but increase pressure.  
* **Resources:** Champions manage resources like health and ability energy/cooldowns.

### **2.3 Player Role: The Warlord (Champion & General)**

* Players create and customize a **Warlord** avatar, who serves as their **primary Champion** and the leader of their faction.  
* The Warlord is a fully playable combatant with their own stats, abilities, and gear, functioning as the first hero on the player's roster.  
* Players **choose** whether to lead raids personally by controlling their Warlord or to send another recruited Champion from their roster instead.  
* In addition to combat prowess, the Warlord has a separate **leadership progression** (skill tree) focused on command perks like increasing the size of their Champion roster, unlocking more Titan slots, improving resource gathering, and potentially granting passive bonuses to their faction.

## **3. Features**

### **3.1 Titan Creation**

* **Foundation:** Players choose a **Titan Lineage** (e.g., Golem, Frost Giant, Dragon - determines base stats, available abilities, visual style).  
* **Appearance:** Modular system. Golems are assembled from elemental rock parts attached to sockets; size/shape can be influenced by stat allocation (e.g., Strength widens arms). Other lineages use similar thematic customization.  
* **Stats:** Allocate points into core combat attributes (Strength, Agility, Magic, Health, Armor) using a **Point-Buy System**. Points are shared across Stats, Abilities, and AI.  
* **Abilities:**  
  * Based on predefined **Ability Definitions** (DA_AbilityDefinition - Primary Data Assets) containing metadata, base parameters, and references to GameplayAbility logic classes.  
  * Players equip abilities into slots based on configuration stored in F_AbilityInstance structs (holds Definition ID, Level, and potential parameter overrides).  
  * System supports both predefined abilities and potentially player-customized versions (using override data within F_AbilityInstance).  
  * Abilities are designed around **implicit synergy** ("Setup & Payoff") and universal keywords with clear visual tells.  
* **AI Pattern Sequencer:**  
  * Players create custom AI logic using a visual editor that defines **Combo Chains** (sequences of ability slots) and a **Priority List** of rules.  
  * Rules use predefined **Conditions** (Target Distance, Health Percentages, Target Status) to trigger **Actions** (Execute Combo X, Use Ability Slot Y).  
  * Allows for creating rhythmic patterns, pauses/delays, and branching logic based on learnable tells, enabling deep strategic and psychological gameplay. AI intelligence/complexity costs points from the shared Point-Buy budget.

### **3.2 Champion Progression & Customization**

* Players acquire and manage a roster of diverse Champions, starting with their Warlord.  
* Champions level up, gaining stats and skill points.  
* Equippable gear system.  
* Customizable ability loadouts selected before starting a raid, potentially allowing adaptation based on intel about the target Titan.

### **3.3 Asynchronous PvP & Matchmaking**

* Players upload their F_LairBuildData (JSON) to a central server (Supabase).  
* Attackers download opponent data to fight locally.  
* Matchmaking based on player rank/level and potentially geographic proximity.  
* Leaderboards track player ranks, Titan win rates, etc.

### **3.4 Overworld Map & Location Anchoring**

* Players anchor their Lairs to real-world locations.  
* **Overworld Representation:** Interactive 3D Globe UI (preferred) or a seamless, walkable world using Cubic/Octahedral projection with room streaming (more complex).  
* **Battle Arena Generation:** Local boss fight arenas are generated using accurate **UTM/UPS** projections based on the Lair's real-world location, providing distortion-free combat environments. Arena appearance potentially themed via a "Biome Texture Atlas" system based on location.

### **3.5 Replay System**

* Uses the "Ghosting" method: records keyframes (Transform, Velocity) and discrete events (Animation Plays, Projectile Spawns) at a fixed interval.  
* Provides visually accurate replays for players to watch their Titan's defensive battles.  
* Input logs recorded separately for potential future server-side anti-cheat validation (using simple sanity checks initially).

### **3.6 Faction Customization**

* Players name their Faction/Warband (led by their Warlord).  
* Design a unique Faction Sigil using a layered emblem creator.  
* Unlock cosmetic Titles based on achievements for their Warlord.

## **4. World & Narrative**

* **Setting:** Modern Earth, radically transformed by the arrival or awakening of magic ("Terra Arcana"). Geography is identical, but overlaid with high-fantasy elements. Cities are fused with Elven architecture, mountains host Dragons, oceans hide Krakens.  
* **Core Principle:** "Spells, Steel, and Titans" (inspired by Guns, Germs, and Steel). Civilizations rose based on their mastery of local magical forces and control over massive, world-shaping creatures (Titans).  
* **Factions:** Diverse fantasy races integrated into real-world locations based on geography and magical affinity (Elves in Paris, Dwarves in Rockies, Krakens off Brazil, etc.). Humans are the adaptable "magitech" faction, found everywhere. "Monster" races (Goblins, Orcs) are universal threats, not tied to specific cultures.  
* **Player Role:** A Warlord rising to power in this chaotic new world, claiming territory and vying for dominance by commanding Champions (including themselves) and designing Titans.  
* **Conflict:** A global struggle for territory and resources (Arcane Energy/Locus), played out through asynchronous PvP battles.

## **5. Art & Audio Style**

* **Art Direction:** Stylized Realism. A blend of familiar modern Earth environments seamlessly integrated with epic high-fantasy elements. Magically transformed landmarks are key visuals.  
* **Titans:** Modular design, especially for Golems (assembled from elemental parts). Other lineages have distinct, imposing aesthetics. Visuals change based on stat allocation and equipped abilities/modifiers.  
* **Champions:** Diverse fantasy hero archetypes with customizable gear.  
* **UI:** Clean, modern, potentially with thematic elements reflecting the chosen ability editor style (Alchemist, Runesmith, Weaver, Magitech).  
* **Audio:**  
  * Epic rock score. Varies depending on chosen Titan lineage.  
  * Impactful combat sound effects emphasizing the scale of Titans.  
  * Potentially thematic voice acting for Warlords/Champions.  
  * **Dynamic Music System:** Music will be a core gameplay mechanic. The soundtrack will sync with boss phases and AI patterns. For example, a fight may begin with an ambient intro track as minions spawn. When the music transitions to its first verse (on a specific measure), the Titan appears. The Titan's AI attack combos will then be programmed to launch in time with the song's measures and phrases. Musical transitions will serve as a primary, learnable "tell" for the attacker to anticipate the boss's next set of patterns, just as important as visual animations.

## **6. Technical Specifications**

* **Engine:** Unreal Engine 5.x  
* **Core Systems:**  
  * Gameplay Ability System (GAS): C++ foundation (AttributeSet, ASC, Base Classes), with primary logic in Blueprints (GameplayAbility, MMCs). Event-driven communication.  
  * AI: State Trees (generic interpreter) reading custom patterns from Data Assets (DA_TitanAI_Pattern). AI Controller acts as "Conductor."  
  * Networking: Async PvP via Supabase backend (PostgreSQL + PostgREST API). Direct HTTP requests from UE5 client for uploading/downloading boss JSON data. No real-time replication needed for core loop.  
  * World Generation: Offline "World Forge" pipeline using GIS data (OSM, potentially terrain/biome/soil data) projected onto chosen overworld system (Globe UI or Polyhedral Streaming). Local arenas generated using UTM/UPS.  
* **Key Data Structures:** F_LairBuildData, F_AbilityInstance, F_EffectDefinition, UDA_AbilityDefinition, UDA_TitanAI_Pattern.

## **7. Monetization (Potential)**

* **Attack Tokens:** Players get free tokens daily; can purchase more for additional attacks.  
* **Cosmetics:** Skins/visual parts for Titans, Champions, Warlords, Faction Sigils.  
* **Convenience:** Faster progression, additional roster slots (carefully balanced to avoid pay-to-win).

## **8. Why Play Terra Arcana?**

* Experience the unique thrill of **designing your own boss** and watching it battle other players.  
* Engage in deep, **skill-based action combat** focused on learning and mastering complex patterns.  
* Explore a familiar yet fantastical version of **modern Earth**.  
* Enjoy endless variety through player-created challenges in an **asynchronous PvP** environment.  
* Build your legacy as a powerful **Warlord** in a world of Spells, Titans, and Steel.