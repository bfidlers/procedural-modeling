from graph_test import create_square
from rules_test import load_square_rules
from graph_transform import *


def test_graph_transform():
    g = create_square()
    print("Before:")
    print(g)
    print("\n")

    rules = load_square_rules()
    rule = random.choice(rules)
    print("Rule:")
    # print(rule.long_string())
    print(rule)
    print("\n")

    apply_rule(rule, g)
    print("After:")
    print(g)


test_graph_transform()