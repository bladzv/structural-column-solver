#include <iostream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include <iomanip>

constexpr double PI = 3.141592653589793;
using namespace std;

static bool valid_positive(double x) { return std::isfinite(x) && x > 0.0; }

static double solve_quadratic_small_root(double c1, double c2) {
    // returns the smaller root of x^2 + c1*x + c2 = 0 using stable sqrt guard
    double disc = c1*c1 - 4.0*c2;
    if (disc < 0.0) disc = 0.0;
    return (-c1 - std::sqrt(disc)) / 2.0;
}

static double euler_load_from_sr(double E, double A, double sr) {
    // original code used: (pi^2 * E * A) / (sr^2)
    return (PI*PI*E*A) / (sr*sr);
}

static double johnson_load(double A, double S, double sr, double E) {
    return (A*S) * (1.0 - (S*sr*sr) / (4.0*PI*PI*E));
}

static double read_positive(const string &prompt) {
    double v = 0.0;
    while (true) {
        cout << prompt;
        if (!(cin >> v)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Invalid input — try again.\n"; continue; }
        if (!valid_positive(v)) { cout << "Value must be positive and finite.\n"; continue; }
        return v;
    }
}

void handle_straight() {
    cout << "\nPlease type if its 1-circular cross section, 2-rectangular cross section: ";
    int option = 0; cin >> option;

    if (option == 1) {
        double diameter = read_positive("Enter the Diameter(D): ");
        double end_fixity = read_positive("Enter the constant end fixity(K): ");
        double length = read_positive("Enter the actual length(L): ");
        double yield_strength = read_positive("Enter the yield strength of material(S): ");
        double elastic_modulus = read_positive("Enter the modulus of elasticity of material(E): ");

        double radius_gyration = diameter / 4.0;
        double area = (PI * diameter * diameter) / 4.0;
        double slenderness_ratio = (end_fixity * length) / radius_gyration;
        double column_constant = std::sqrt((2.0 * PI * PI * elastic_modulus) / yield_strength);

        cout << fixed << setprecision(6);
        cout << "Radius of gyration: " << radius_gyration << "\n";
        cout << "Area: " << area << "\n";
        cout << "Slenderness ratio: " << slenderness_ratio << "\n";
        cout << "Column constant: " << column_constant << "\n";

        if (slenderness_ratio > column_constant) {
            cout << "The column is long, so use Euler's formula." << "\n";
            double euler_P = euler_load_from_sr(elastic_modulus, area, slenderness_ratio);
            cout << "Critical Load (Euler): " << euler_P << "\n";
        } else {
            cout << "The column is short — use Johnson's formula." << "\n";
            double johnson_P = johnson_load(area, yield_strength, slenderness_ratio, elastic_modulus);
            cout << "Critical Load (Johnson): " << johnson_P << "\n";
        }
    } else if (option == 2) {
        double breadth = read_positive("Enter the base(B): ");
        double height = read_positive("Enter the height(H): ");
        double length = read_positive("Enter the length(L): ");
        double end_fixity = read_positive("Enter the constant end fixity(K): ");
        double yield_strength = read_positive("Enter the yield strength of material(S): ");
        double elastic_modulus = read_positive("Enter the modulus elasticity of material(E): ");

        double radius_gyration = breadth / std::sqrt(12.0);
        double area = breadth * height;
        double slenderness_ratio = (end_fixity * length) / radius_gyration;
        double column_constant = std::sqrt((2.0 * PI * PI * elastic_modulus) / yield_strength);

        cout << fixed << setprecision(6);
        cout << "Radius of gyration: " << radius_gyration << "\n";
        cout << "Area: " << area << "\n";
        cout << "Slenderness ratio: " << slenderness_ratio << "\n";
        cout << "Column constant: " << column_constant << "\n";

        if (slenderness_ratio > column_constant) {
            cout << "The column is long, so use Euler's formula." << "\n";
            double euler_P = euler_load_from_sr(elastic_modulus, area, slenderness_ratio);
            cout << "Critical Load (Euler): " << euler_P << "\n";
        } else {
            cout << "The column is short — use Johnson's formula." << "\n";
            double johnson_P = johnson_load(area, yield_strength, slenderness_ratio, elastic_modulus);
            cout << "Critical Load (Johnson): " << johnson_P << "\n";
        }
    } else {
        cout << "Invalid option." << "\n";
    }
}

void handle_crooked() {
    cout << "\nPlease type if its 1-circular cross section, 2-rectangular cross section" << "\n";
    int option = 0; cin >> option;

    if (option == 1) {
        double diameter = read_positive("Enter the diameter(D): ");
        double end_fixity = read_positive("Enter the constant end fixity(K): ");
        double initial_crookedness = read_positive("Enter the initial crookedness(a): ");
        double design_factor = read_positive("Enter the design factor(N): ");
        double length = read_positive("Enter the actual length(L): ");
        double yield_strength = read_positive("Enter the yield strength of material(s): ");
        double elastic_modulus = read_positive("Enter the modulus of elasticity of materials(E): ");

        double radius_gyration = diameter / 4.0;
        double area = (PI * diameter * diameter) / 4.0;
        double slenderness_ratio = (end_fixity * length) / radius_gyration;
        double column_constant = std::sqrt((2.0 * PI * PI * elastic_modulus) / yield_strength);
        double half_section = diameter / 2.0;

        cout << fixed << setprecision(6);
        cout << "Radius of gyration: " << radius_gyration << "\n";
        cout << "Area: " << area << "\n";
        cout << "Slenderness ratio: " << slenderness_ratio << "\n";
        cout << "Column constant: " << column_constant << "\n";

        if (slenderness_ratio > column_constant) {
            double euler_P = euler_load_from_sr(elastic_modulus, area, slenderness_ratio);
            double init_crooked_term = (initial_crookedness * half_section) / (radius_gyration * radius_gyration);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + init_crooked_term) * euler_P);
            double quad_c2 = (yield_strength * area * euler_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Euler): " << euler_P << "\n";
            cout << "C1: " << quad_c1 << "\n";
            cout << "C2: " << quad_c2 << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
        } else {
            double johnson_P = johnson_load(area, yield_strength, slenderness_ratio, elastic_modulus);
            double init_crooked_term = (initial_crookedness * half_section) / (radius_gyration * radius_gyration);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + init_crooked_term) * johnson_P);
            double quad_c2 = (yield_strength * area * johnson_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Johnson): " << johnson_P << "\n";
            cout << "C1: " << quad_c1 << "\n";
            cout << "C2: " << quad_c2 << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
        }

    } else if (option == 2) {
        double breadth = read_positive("Enter the base(B): ");
        double height = read_positive("Enter the height(H): ");
        double length = read_positive("Enter the length(L): ");
        double design_factor = read_positive("Enter the design factor: ");
        double end_fixity = read_positive("Enter the constant end fixity: ");
        double yield_strength = read_positive("Enter the yield strength of material: ");
        double elastic_modulus = read_positive("Enter the modulus of elasticity: ");

        double radius_gyration = breadth / std::sqrt(12.0);
        double area = breadth * height;
        double slenderness_ratio = (end_fixity * length) / radius_gyration;
        double column_constant = std::sqrt((2.0 * PI * PI * elastic_modulus) / yield_strength);

        cout << fixed << setprecision(6);
        cout << "Radius of gyration: " << radius_gyration << "\n";
        cout << "Area: " << area << "\n";
        cout << "Slenderness ratio: " << slenderness_ratio << "\n";
        cout << "Column constant: " << column_constant << "\n";

        if (slenderness_ratio > column_constant) {
            double euler_P = euler_load_from_sr(elastic_modulus, area, slenderness_ratio);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + 0.0) * euler_P);
            double quad_c2 = (yield_strength * area * euler_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Euler): " << euler_P << "\n";
            cout << "C1: " << quad_c1 << "\n";
            cout << "C2: " << quad_c2 << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
        } else {
            double johnson_P = johnson_load(area, yield_strength, slenderness_ratio, elastic_modulus);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + 0.0) * johnson_P);
            double quad_c2 = (yield_strength * area * johnson_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Johnson): " << johnson_P << "\n";
            cout << "C1: " << quad_c1 << "\n";
            cout << "C2: " << quad_c2 << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
        }

    } else {
        cout << "Invalid option." << "\n";
    }
}

void handle_eccentric() {
    cout << "\nPlease type if its 1-circular cross section, 2-rectangular cross section" << "\n";
    int option = 0; cin >> option;

    if (option == 1) {
        double diameter = read_positive("Enter the diameter(D) :");
        double end_fixity = read_positive("Enter the constant end fixity(K): ");
        double initial_crookedness = read_positive("Enter the initial crookedness(a): ");
        double design_factor = read_positive("Enter the design factor(N): ");
        double length = read_positive("Enter the actual length(L): ");
        double yield_strength = read_positive("Enter the yield strength of material(S): ");
        double elastic_modulus = read_positive("Enter the modulus of elasticity of material(E): ");
        double eccentricity = read_positive("Enter the eccentricity(e): ");

        double radius_gyration = diameter / 4.0;
        double area = (PI * diameter * diameter) / 4.0;
        double slenderness_ratio = (end_fixity * length) / radius_gyration;
        double column_constant = std::sqrt((2.0 * PI * PI * elastic_modulus) / yield_strength);
        double half_section = diameter / 2.0;

        cout << fixed << setprecision(6);
        cout << "Radius of gyration: " << radius_gyration << "\n";
        cout << "Area: " << area << "\n";
        cout << "Slender ratio: " << slenderness_ratio << "\n";
        cout << "Column constant: " << column_constant << "\n";
        cout << "Eccentricity: " << eccentricity << "\n";

        if (slenderness_ratio > column_constant) {
            double euler_P = euler_load_from_sr(elastic_modulus, area, slenderness_ratio);
            double init_crooked_term = (initial_crookedness * half_section) / (radius_gyration * radius_gyration);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + init_crooked_term) * euler_P);
            double quad_c2 = (yield_strength * area * euler_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Euler): " << euler_P << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
            cout << "Approx. Maximum Stress: " << (allowable_load/area) << " (load/area)\n";
        } else {
            double johnson_P = johnson_load(area, yield_strength, slenderness_ratio, elastic_modulus);
            double init_crooked_term = (initial_crookedness * half_section) / (radius_gyration * radius_gyration);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + init_crooked_term) * johnson_P);
            double quad_c2 = (yield_strength * area * johnson_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Johnson): " << johnson_P << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
            cout << "Approx. Maximum Stress: " << (allowable_load/area) << " (load/area)\n";
        }

    } else if (option == 2) {
        double breadth = read_positive("Enter the base(B): ");
        double height = read_positive("Enter the height(H): ");
        double length = read_positive("Enter the length(L): ");
        double design_factor = read_positive("Enter the design factor(N): ");
        double end_fixity = read_positive("Enter the constant end fixity(K): ");
        double yield_strength = read_positive("Enter the yield strength of material(S): ");
        double elastic_modulus = read_positive("Enter the modulus of elasticity(E): ");
        double eccentricity = read_positive("Enter the eccentricity(e): ");

        double radius_gyration = breadth / std::sqrt(12.0);
        double area = breadth * height;
        double slenderness_ratio = (end_fixity * length) / radius_gyration;
        double column_constant = std::sqrt((2.0 * PI * PI * elastic_modulus) / yield_strength);


        cout << fixed << setprecision(6);
        cout << "Radius of gyration: " << radius_gyration << "\n";
        cout << "Area: " << area << "\n";
        cout << "Slenderness ratio: " << slenderness_ratio << "\n";
        cout << "Column constant: " << column_constant << "\n";
        cout << "Eccentricity: " << eccentricity << "\n";

        if (slenderness_ratio > column_constant) {
            double euler_P = euler_load_from_sr(elastic_modulus, area, slenderness_ratio);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + 0.0) * euler_P);
            double quad_c2 = (yield_strength * area * euler_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Euler): " << euler_P << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
            cout << "Approx. Maximum Stress: " << (allowable_load/area) << " (load/area)\n";
        } else {
            double johnson_P = johnson_load(area, yield_strength, slenderness_ratio, elastic_modulus);
            double quad_c1 = (-1.0 / design_factor) * ((yield_strength * area) + (1.0 + 0.0) * johnson_P);
            double quad_c2 = (yield_strength * area * johnson_P) / (design_factor * design_factor);
            double allowable_load = solve_quadratic_small_root(quad_c1, quad_c2);
            cout << "Critical Load (Johnson): " << johnson_P << "\n";
            cout << "Allowable Load: " << allowable_load << "\n";
            cout << "Approx. Maximum Stress: " << (allowable_load/area) << " (load/area)\n";
        }

    } else {
        cout << "Invalid option." << "\n";
    }
}

int main() {
    while (true) {
        cout << "<----------MENU---------->" << "\n";
        cout << "Welcome to Column Solver" << "\n";
        cout << "1 - Straight column\n2 - Crooked column\n3 - Eccentric column\n";
        cout << "Select from the following (0 to exit): ";

        int opt = -1;
        if (!(cin >> opt)) { break; }
        if (opt == 0) break;

        switch (opt) {
            case 1: handle_straight(); break;
            case 2: handle_crooked(); break;
            case 3: handle_eccentric(); break;
            default: cout << "Invalid selection\n"; break;
        }

        cout << "\nBack to main menu? (y/n): ";
        char c; cin >> c;
        if (!(c == 'y' || c == 'Y')) break;
    }

    cout << "\nThank you for using the system\n";
    return 0;
}

