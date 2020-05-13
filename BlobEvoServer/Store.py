from enum import Enum
import random

# SPEED = 0
# SIZE = 1
# RADAR = 2
# ENDURENCE = 3
# CANIBBALIZM = 4

# FOG = 0
# IRON_SKIN = 1
# DETIRIORAITON = 2
# TOUGH_TERRIAN = 3
# AIR_POLLUTION = 4

class Store:
    def __init__(self, player_count:int, items_per_player:int):
        self.current_genes = []
        self.current_elements = []
        self.items_per_player = items_per_player

        for i in range(0, player_count * items_per_player):
            self.current_genes.append(self.generate_id_couple())
            self.current_elements.append(self.generate_id_couple())

    def buy_element(self, id:int):
        self.current_elements[id] = self.generate_id_couple()
    
    def buy_gene(self, id:int):
        self.current_genes[id] = self.generate_id_couple()

    def generate_id_couple(self):
        first_id = random.randint(0, 4)
        second_id = random.randint(0, 4)
        
        while first_id == second_id:
            second_id = random.randint(0, 4)
        
        return (first_id, second_id)

    def get_new_gene_set(self):
        items = []

        for i in range(0, self.items_per_player):
            candidate = random.randint(0, len(self.current_genes))
            while candidate in items:
                candidate = random.randint(0, len(self.current_genes))

            items.append(candidate)

        return items

    def get_new_element_set(self):
        items = []

        for i in range(0, self.items_per_player):
            candidate = random.randint(0, len(self.current_elements))
            while candidate in items:
                candidate = random.randint(0, len(self.current_elements))

            items.append(candidate)

        return items

    def get_element(self, id:int):
        if id < len(self.current_elements):
            return self.current_elements[id]
        else:
            return None

    def get_gene(self, id:int):
        if id < len(self.current_genes):
            return self.current_genes[id]
        else:
            return None


def main():
    store = Store(4, 3)
    
    print("Store elements:")
    for element in store.current_elements:
        print(element)
    
    print("\nStore genes:")
    for gene in store.current_genes:
        print(gene)

if __name__ == "__main__":
    main()