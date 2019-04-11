class Dog
  attr_accessor :name, :fangs , :tail

  def initialize(name="Pochi")
    @name = name
    @fangs = 2
    @tail = 1
  end


  def alived?
      true
  end
  def dead?
    true
  end
end
