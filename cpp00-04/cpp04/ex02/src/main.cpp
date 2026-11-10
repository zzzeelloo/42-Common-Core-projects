/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:39:10 by zcherif           #+#    #+#             */
/*   Updated: 2025/11/01 11:39:13 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main(void)
{
    // --- Polimorphism and destruction by base ---
    const int N = 6;
    Animal* animals[N];

    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Cat();
    animals[3] = new Dog();
    animals[4] = new Cat();
    animals[5] = new Dog();

    std::cout << std::endl << "- - - Polimophic Sounds / Check the main.cpp array - - - " << std::endl;
    for (int i = 0; i < N; ++i)
        animals[i]->makeSound();   // <- polimorphism proof

    std::cout << std::endl;

    for (int i = 0; i < N; ++i)
        delete animals[i];
    return (0);
}

/*

          ┌────────────────────────┐
          │      Animal (abstract) │
          │────────────────────────│
          │ - type : std::string   │
          │────────────────────────│
          │ + getType() const      │
          │ + makeSound() = 0 🔸   │ ← pure virtual method
          │ + virtual ~Animal()    │
          └──────────┬─────────────┘
                     │
     ┌───────────────┴────────────────┐
     │                                │
┌──────────────┐               ┌──────────────┐
│    Dog       │               │    Cat       │
│──────────────│               │──────────────│
│ + Brain*     │               │ + Brain*     │  ← both OWN a Brain
│──────────────│               │──────────────│
│ + makeSound()│ → "Woof Woof" │ + makeSound()│ → "Meow Meow"
└───────┬──────┘               └───────┬──────┘
        │                              │
   ┌────▼─────┐                   ┌────▼─────┐
   │  Brain   │                   │  Brain   │
   │100 ideas │                   │100 ideas │
   └──────────┘                   └──────────┘


Key facts (CPP04):
- ex02 (Abstract): Animal is NOT instantiable; makeSound() is pure virtual (=0).
- ex01 (Brain & deep copy): each Dog and Cat allocates its OWN Brain with new Brain().

Memory management (Rule of Three on Dog/Cat):
- Constructor: new Brain().
- Destructor: delete Brain (no leaks).
- Copy constructor / operator=: DEEP COPY (clone Brain’s 100 ideas); NEVER share pointers.

Polymorphism:
- Use Animal* (or Animal&) to store Dogs/Cats.
- Calling animals[i]->makeSound() resolves to Dog/Cat at runtime (dynamic dispatch).
- Virtual destructor in Animal ensures deleting via Animal* calls the proper derived destructor.

Construction / Destruction order:
- Construct: Animal (base) → Dog/Cat (derived) → Brain.
- Destruct: Brain → Dog/Cat (derived) → Animal (base).

Testing checklist:
- Create array of Animal* with mixed Dog/Cat; loop makeSound() (polymorphism).
- Delete all via Animal* (no leaks; correct destructor chain).
- Deep copy check: copy a Dog/Cat, mutate original Brain; copied Brain must remain unchanged.

Gotchas:
- Do NOT instantiate Animal directly in ex02.
- Avoid object slicing (use pointers/references to base).
- Ensure makeSound() signature in Dog/Cat EXACTLY matches Animal’s (const vs non-const).

*/