classdef Relu
    properties
        name;
        input;
        output;
        delta;
    end
    
    methods
        function layer = Relu(name)
            layer.name = name;
        end
        
        function layer = forward(layer, input)
            layer.input = input;
            layer.output = max(layer.input, 0);
        end
        
        function layer = backprop(layer, delta)
            relu = zeros(size(delta));
            relu(layer.output > 0) = 1;
            layer.delta = relu.*delta;
        end
    end
end
