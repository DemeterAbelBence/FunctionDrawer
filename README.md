# FunctionDrawer

The program expects a formula f(x, y) = z, that represents a two variable function. This formula can be specified as a string by the user, which is then translated into mathematical operations using a recursive evaluator algorithm. This algorithm, simultaneously with the formula evaluation, calculates the total derivative at each x and y, in other words the normal at each vertex. For this calculation automatic differentiation and dual numbers are used. Now that the vertex data is calculated, the rendering phase can begin with Phong Shading. 

![image](https://github.com/DemeterAbelBence/FunctionDrawer/assets/124840546/93efad0f-7b60-43b6-8e0b-9e24b8fe0299)

