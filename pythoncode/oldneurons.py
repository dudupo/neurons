

from random import random
from math import log , e

'''
				strategys
			|--------------
	states	|
			|
			|
		
			P*(q , s) = P(q , s) + h(q , s)
			Sum(P(q,s)) + Sum(h(q ,s)) = 1 | for s in S 

'''
		
class Neurones():

	def __init__(self):
		self.Layers = []
		self.Remember = 1
		self.samples = []
		self.Rate = -20
	def _calculate(self , inputs):
		
		for layer in self.Layers:
			inputs = layer._calculate(inputs)
			
		return inputs

	def path(self , layer , synapse):
		ret = 0

		inputs = [0 for _ in self.Layers[layer]._len_inputs]
		inputs[synapse] = 1

		for _layer in self.Layers[layer:]:
			inputs = _layer._calculate(inputs) 

		return inputs

	def optimize(self , samples):
		
		def _calculate_eror(self , sample):
			_input , _output = sample
			return (self._calculate(_input) - _output)**2   

		def dlogistic(z):
			return e**-z / ((1 + e**-z)**2)

		def _optimize(layers , inputs , results , Rate = -10):
			
			if len(layers) == 0:			
				deltas = [dlogistic(_input) * (_input - result) for _input , result in zip(inputs , results)]
				return deltas

			layer = layers.pop(0)
			__inputs = layer._calculate(inputs)
			deltas = _optimize(layers , __inputs , results)
			
			derivatives = {}

			_new_deltas = [0 for _ in range(layer._len_inputs)]
			for synapses , (i ,j) in layer:
				derivatives[i,j] = inputs[i] * deltas[j] * Rate
				layer.synapses[i,j] = synapses[i,j] + derivatives[i,j]
				_new_deltas[i] += deltas[j] * layer.synapses[i,j]

			for j , _input in enumerate(inputs):
				_new_deltas[j] *= dlogistic(_input)

			self.Layers = [layer] +  self.Layers
			return _new_deltas

		
		#self.samples += samples
		#self.samples = samples[-self.Remember:]
		#samples = self.samples
		
		while self.cost(samples) > 0.2:
			for sample in samples:
				inputs , results = sample
				_optimize(self.Layers , inputs , results , min(0,self.Rate))
		
		#self.Rate += 0.5
		pass
	def cost(self , samples):
		ret = float(0) 
		for sample in samples:
			inputs , results = sample
			ret += self._distance(self._calculate(inputs) , results)
		return ret

	def _distance(self ,X , Y):
		ret = float(0)
		for (x ,y) in zip(X , Y):
			ret += (y-x)**2
		ret =float(ret ** 0.5)
		return ret

	def _gradient_descent(position , derivative , cost=0.01 , difference = 0.01):
		_next = [_position - _derivative(_position)*difference for _position , _derivative in zip(position,_derivative)]
		if _distance(_next , position) < cost:
			return _next
		else:
			return _gradient_descent(_next , derivative , cost , difference)

	def __iter__(self):
		for layer in self.Layers:
			for synapses , synapse in layer:
				yield synapses , synapse

class Layer():
	def __init__(self , _len_inputs , _len_outpus):
		self.synapses = {(i,j):0 for i in range(_len_inputs) for j in range(_len_outpus)}
		self._len_inputs = _len_inputs
		self._len_outpus = _len_outpus

		
	def _calculate(self , inputs):

		def _normate(z):
			return 1/(1 + (e**-z))

		out = [0 for j in range(self._len_outpus)]
		for j in range(self._len_outpus):
			for i in range(self._len_inputs):
				out[j] += self.synapses[i ,j]*inputs[i]
			out[j] = _normate(out[j])
		return out

	def __iter__(self):
		for i in range(self._len_inputs):
			for j in range(self._len_outpus):
				yield self.synapses , (i,j)



if __name__ == "__main__":

	N = Neurones()

	l1 = Layer(2 ,2)
	l2 = Layer(2 , 4)

	l2.synapses[0,1] = 0.4
	l2.synapses[0,2] = 0.3
	l1.synapses[0,0] = 0.5
	l1.synapses[0,1] = 0.5

	N.Layers = [l1 , l2]

	samples = [[[0.1,0.7],[0.1,0.3,1,0.8]],
		[[0.2,0.7],[0.1,0.3,1,0.8]],
		[[0.3,0.7],[0.1,0.3,1,0.8]],
		[[0.4,0.7],[0.1,0.3,1,0.8]]]

	N.optimize(samples)
	
	print  N._calculate([0.6,0.7])
	print  N._calculate([0.2,0.8])
	print  N._calculate([1 ,0])

	'''
		E = Sum[(y - y*)^2]  ... y* -> ouer network , y-> the correct output . 
			lets look on the last layer , dE/dw = dE/dz * dz/dw -> f`(z) * O(m)

	'''